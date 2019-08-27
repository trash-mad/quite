
# Рендеринг пользовательского интерфейса

## JSX factory

Данный фреймворк дублирует [jsx синтаксис](https://ru.react.js.org/docs/introducing-jsx.html) и систему компонентов известной каждому разработчику библиотеки React. Для подключения требуется изменить поле jsxFactory в объекте конфигурации транспилятора TypeScript. 

tsconfig.json
```
{
    "jsxFactory": "Quite.createElement",
    ...
}
```

JSX это упрощенный синтаксис функции создания элемента, обладающего следующим прототипом. Параметр type является либо строковым идентификатором элемента, либо инстанцией объекта компонента (об этом ниже по тексту). Параметр props содержит либо null, либо объект свойств элемента. Параметр child является не обязательным и содержит перечисление дочерних элементов через запятую. Ближайший аналог из [C++](https://en.wikipedia.org/wiki/Variadic_function), [C#](https://docs.microsoft.com/ru-ru/dotnet/csharp/language-reference/keywords/params), [ES6](https://developer.mozilla.org/ru/docs/Web/JavaScript/Reference/Functions/Rest_parameters). Вообще это называется оставшиеся параметры.  

```
//Quite.render(type,props,child...)

Quite.render(
    Quite.createElement("Window",{alignItems:"center",justifyContent:"center"}
        Quite.createElement("Rectangle", {height: 100, width: 100, color: "red"}
            Quite.createElement("Rectangle",null,
                Quite.createElement("Text",{
                    text:"text with bounding rect in top left corner of red rectangle"
                })
            )
        )
    )
);
```

Корневым компонентом обязательно должно быть окно (type: "Window"). Последний передается в функцию render() для пометки на игнорирование сборщиком мусора и непосредственно открытие оного. Подробнее о рендеринге элементов будет написано ниже.

## Компонент

Компонент это объект, прототип которого содержит функцию render. Последняя исполняется фреймворком при вызове this.setState компонента для получения нового древа для отображения.

```

function Test(props) {
    console.log(JSON.stringify(props));
    this.state={
        text:0
    }
}

Test.prototype.clickHandler=function() {
    console.log("clicked");
    this.setState({text:this.state.text+1})
}

Test.prototype.render=function() {
    return Quite.createElement("Button", {text:this.state.text,onClick:this.clickHandler})
}

Quite.render(Quite.createElement("Window", null, 
    Quite.createElement(Test,{testProp:"omg"})
));

// 0 -> 1 -> 2 -> 3 -> ...

```

Функция setState подставляется прототипу объекта при создании компонента через Quite.createElement и не доступна со стороны языка JavaScript. Её реализация написана на C++, а дергаем мы по факту binding. Из этого вытекает серъезный плюс: отсутствие классов-родителей как зависимости, возможность применения ООП парадигмы без множественного наследования.

## Подробнее о рендеринге. Diff алгоритм.

Функция Quite.render полностью рисует всё древо компонентов. Это единоразовое неизбежное зло - никуда не денешься, но и по жизни не приследует. Однако, с вызовом this.setState ситуация координально другая - компоненты меняют свое состояние постоянно. Библиотека реализует как самый топорный полный ререндеринг поддрева (это нормально, пока не используем состояния вида Redux), так и рендеринг изменений с применением Diff алгоритма.

### Применение минимального количества изменений
Первый рендер древа компонента выполняется полностью (топорно). Последующие происходят с применением минимального количества изменений (shortest edit script). Применение изменений осложняется тем, что после вызова функции render у компонента во второй раз и далее, мы имеем два физически разных древа. Элементы древ необходимо сопоставить между собой, об этом ниже.

Изменения существуют трех видов:

 - COMMON
  Элементы без изменения требуют отдельного сравнения props и перерисовки в частном порядке. ~~Алгоритм "сортировка пузырьком" вполне справится,~~ ничего принципиально сложного. У фреймворка строковое представление полей объекта свойств являются ключами хеш-таблицы.
 - DELETE
  Удаление элементов. Ещё проще, чем общие элементы, так как имеем указатель на первое древо.
 - NEW

    Самое сложное. Требует детального описания (ниже).
  
  1. Новые главенствующие потомки (обозначим как **appendChild**)
    Первый потомок в списке, нет указателя на ноду, перед которой вставляем.
  2. Новые втростепенные потомки  (обозначим как **insertAfterChild**)
    Потомок вставляется перед каким-либо элементом, имея общий с родитель.
  3. Новый корневой элемент компонента (ничтожно редко)
    По факту полностью заменяет всё дочернее древо компонента ~~Прикладной программист не был трезв в процессе написания компонента.~~

### Приведение древ к строковому виду
Для исполнения алгоритма поиска изменений (shortest edit script) нам необходимо привести древо объектов в строковый вид. Делается это простенькой рекурсивной функцией, ниже я размещу её реализацию в псевдокоде, а так же, для простоты понимания, графическое представление результата работы.

C#-like sometimes (out, array declaration syntax) code
```
void countTotalElements(Element root, out int total=0) {
    total+=1
    for (int i=0;i!=root.child.length;i++) {
        countTotalElements(root.child[i], total)
    }
    return total
}


void buildElementTree(Element root, out vector<Element> result, out int index=0) {
    result[index]=root
    index++
    for (int i=0;i!=root.child.length;i++) {
        buildElementTree(root.child[i], result, index)
    }
}

Element root = new Element() {
    type: "a",
    child: {
        new Element() {
            type: "b",
            child: {
                new Element() {
                    type: "c"
                },
                new Element() {
                    type: "d"
                }
            }
        }
        new Element() {
            type: "e"
        }
    }
}

//      a
//     / \
//    b   e
//   / \
//  c   d
//

vector<Element> sequence = new vector<Element>(countTotalElements(root))

buildElementTree(root, sequence)

// a b c d e
// ----------->

```

Функция спускаеться по дереву, пробегая потомков текущего корневго элемента с лева на право (от нуля до кол-ва потомков). Если визуализировать её работу, то можно заметить, что мы всегда движемся по древу в приоретете налево. На этом и основывается сопоставление элементов: слева родители и соседи, а справа соседи и потомки.

### Сопоставление нод
Теперь найдем одинаковые элементы у двух древ. Пусть класс Element средствами стандартной библиотеки псевдокода реализует метод parent(), который возвращает родителя элемента (в реальном коде он передается при Quite.createElement). Так же добавим поле key, зачем оно нужно я опишу ниже.

C#-like sometimes (out, array declaration syntax) code
```
//        a1
//       /  \
//     b1   e1
//    /  \
//   c1  d1

Element currentTree = new Element() {
    key: 0
    type: "elem",
    child: {
        new Element() {
            type: "elem",
            child: {
                new Element() {
                    key: 1,
                    type: "elem"
                },
                new Element() {
                    key: 2,
                    type: "elem"
                }
            }
        }
        new Element() {
            key: 3,
            type: "elem"
        }
    }
}

//         a2
//        /
//      b2
//    / |  \
//   c2 d2 e2

Element newTree = new Element() {
    key: 0,
    type: "elem",
    child: {
        new Element() {
            type: "elem",
            child: {
                new Element() {
                    key: 1,
                    type: "elem"
                },
                new Element() {
                    key: 2,
                    type: "elem"
                },
                new Element() {
                    key: 3,
                    type: "elem"
                }
            }
        }
    }
}

```

Мы сравниваем type, key выбранных двух элементов, поднимаемся до их родителей, и, если у обоих элементов они существуют, сравниваем пока оба не будут null. Пример:

C#-like sometimes [REPL](https://ru.wikipedia.org/wiki/REPL)
```
// Сравниваем e1 и e2
//   a1          a2
//      \       /
//       e1    b2
//              \
//              e2

> e1.key==e2.key&&e1.type==e2.type
true
// Идем выше по древу

> a1.key==b2.key&&a1.type==b2.type
true
// Конкректно сейчас true. Но по факту, тип родителя чаще всего разный и мы прервемся уже тут

> a2.key==?
exception
// Вот мы и остановились. В ветке 2 остались родители, а ветка 1 закончилась
```




В методе, представленным псевдокодом выше, есть фундаментальная проблема. Он упращен намеренно. 