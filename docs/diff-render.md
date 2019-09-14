
# Рендеринг пользовательского интерфейса

## JSX factory

Данный фреймворк дублирует [jsx синтаксис](https://ru.react.js.org/docs/introducing-jsx.html) и систему компонентов известную каждому разработчику библиотеки React. Для подключения требуется изменить поле jsxFactory в объекте конфигурации транспилятора TypeScript. 

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

## JSX вложенные списки

Часто при разработке пользовательского интерфейса с применением ReactJS встает вопрос о выводе списка элементов. Официальное [руководство](https://reactjs.org/docs/lists-and-keys.html) от FaceBook описывает вывод списка с ипользованием функции `Array.prototype.map()`. Последняя возвращает измененный список, где каждый элемент подвергся моддификации функцией из аргументов.

```
function NumberList() {
    this.state={numbers:[1,2,3]};
}

NumberList.prototype.render=function(props) {
  const numbers = this.state.numbers;
  return (
    <ul>
      <p value="Header"/>
      {numbers.map((number) =>
        <li key={number} value={number} />
      )}
    </ul>
  );
}
```

После транспиляции и исполнения рендеринга компонента поддрево будет эквивалентно следующему представлению:

```
render(
    Quite.createElement("ul",null,
        Quite.createElement("p",{value:"Header"}), [
            Quite.createElement("li",{key:1,value:1}),
            Quite.createElement("li",{key:2,value:2}),
            Quite.createElement("li",{key:3,value:3})
        ]
    )
);
```

Примечательно, что ul имеет два физических потомка в аргументах, один из которых выражен массивом. Кроме того, подобные массивы могут быть вложенными (map() внутри map()). Для решения проблемы JSX factory данного фреймворка осуществляет приведение массива к [плоскому](https://developer.mozilla.org/ru/docs/Web/JavaScript/Reference/Global_Objects/Array/flat) виду, используя код эквивалентный по логике работы для `Array.prototype.flat(Infinity)`.


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

Функция setState подставляется прототипу объекта при создании компонента через Quite.createElement и не доступна со стороны языка JavaScript. Её реализация написана на C++, а дергаем мы по факту binding. Из этого вытекает серьезный плюс: отсутствие классов-родителей как зависимости, возможность применения ООП парадигмы без множественного наследования.

## Подробнее о рендеринге. Diff алгоритм.

Функция Quite.render полностью рисует всё древо компонентов. Это единоразовое неизбежное зло - никуда не денешься, но и по жизни не преследует. Однако, с вызовом this.setState ситуация кардинально другая - компоненты меняют свое состояние постоянно. Библиотека реализует как самый топорный полный рендеринг поддрева (это нормально, пока не используем состояния вида Redux), так и рендеринг изменений с применением Diff алгоритма.

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
    Первый потомок в списке у родителя, нет указателя на элемент, перед которой вставляем.
  2. Новые второстепенные потомки  (обозначим как **insertAfterChild**)
    Потомок вставляется перед каким-либо элементом (соседом), имея общий с родитель.
  3. Новый корневой элемент компонента (ничтожно редко)
    По факту полностью заменяет всё дочернее древо компонента ~~Прикладной программист не был трезв в процессе написания компонента.~~

### Приведение древ к строковому виду
Для исполнения алгоритма поиска изменений (shortest edit script) нам необходимо привести древо объектов в строковый вид. Делается это простенькой рекурсивной функцией, ниже я размещу её реализацию в псевдокоде, а также, для простоты понимания, графическое представление результата работы.

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

Функция спускается по дереву, пробегая потомков текущего корневого элемента с лева на право (от нуля до кол-ва потомков). Если визуализировать её работу, то можно заметить, что мы всегда движемся по древу в приоритете налево. На этом и основывается сопоставление элементов: слева родители и соседи, а справа соседи и потомки.

### Сопоставление элементов
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
// Конкретно сейчас true. Но по факту, тип родителя чаще всего разный и мы прервемся уже тут

> a2.key==?
exception
// Вот мы и остановились. В ветке 2 остались родители, а ветка 1 закончилась
```

Итого, реализация сравнения у класса Element будет выражена примерно такой рекурсивной функцией. Положительным результатом работы является значение null в результате вызова parent() у обоих элементов.

C#-like sometimes [REPL](https://ru.wikipedia.org/wiki/REPL)
```
bool compare(Element a, Element b, bool recursive=true) {
    if (a.key!=b.key) {
        return false;
    } else if (a.type!=b.type) {
        return false;
    } else if (recursive) {
        const Element* parent1 = a;
        const Element* parent2 = b;
        while(true) {
            parent1 = parent1.parent(); // Откуда parent() взялся см выше
            parent2 = parent2.parent();
            if (parent1==null&&parent2==null) {
                return true;
            } else if (parent1==null&&parent2!=null) {
                return false;
            } else if (parent1!=null&&parent2==null) {
                return false;
            } else if (!equals(parent1, parent2, false)) {
                return false;
            } else {
                continue;
            }
        }
    } else {
        return true;
    }
}
```

### Как именно из реализации сравнения двух элементов и построения строкового представления получается shortest edit script
Всё очень просто. Есть готовый [алгоритм](https://ru.wikipedia.org/wiki/Diff) и [готовая](https://github.com/cubicdaiya/dtl) утилита сравнения, построенная с применением генериков. Японцы исполнительные, но без фантазии...

C#-like sometimes [REPL](https://ru.wikipedia.org/wiki/REPL)
```
//    a
//   / \
//  b   b 
//       \
//        c
//
// a-b-b-c
```

Абсолютно ничего страшного, что символы могут повторяться. Действительно, сравнение как для строк абсолютно покрывает наши потребности. Так же, утилита дает выхлоп как нам и нужно. Поэтому, рассмотрим её работу как [атомарную](https://ru.wikipedia.org/wiki/Атомарная_операция) операцию. Утилита дает последовательность с примененным изменением **merged**, список общих элементов **common**, список элементов к удалению **delete** и список новых элементов **new**.

### Применение списка изменений на реальное древо.
Всё ещё остается проблема, что часть элементов не являются частью реального древа и не промаплены в реальном мире. И так, алгоритм. Библиотека dtl любезно оборачивает список изменений (shortest edit script)  в свои объекты так, что мы можем узнать индекс элемента текущего древа сопоставленным с индексом элемента нового древа (по аналогии с [std::pair](https://ru.cppreference.com/w/cpp/utility/pair)) и прочую информацию. Также, мы можем узнать тип изменения. Частичная реализация применения изменений в псевдокоде. Далее по тексту я буду обозначать shortest edit script как ses. 

Функция **apply()** ниже отбрасывает дочерние элементы с поправкой на вложенность как на графе a1. Функция **processChild()** в данном сегменте рассмотрена в виде неделимой операции, её реализацию я опишу ниже.

Simplified js-like code
```
//
//  Метод **apply()** пропускает дочерние элементы у новых в списке - родительский элемент b21
//  будет срендерен вместе с потомками b22, b23, b24
//
//          a1
//        /   \
//      b1     c1
//                    
//
//              a2
//            /   \
//          b2     c2
//         /
//       b21 
//     /  |  \
//   b22 b23 b24
//


void apply(ses, merged) {
    list<Element> parents;
    ses::iterator iter;
    bool found=false;
    for (iter=ses.begin();iter!=ses.end();iter++) {
        pair=iter.item;
        if (pair.type==COMMON) {
            // Передаем новые свойства в элемент на сопоставление
            pair.current.commitProps(parrent.new.props) 
        } else if (pair.type==DELETE) {
            // Оповещаем ноду о необходимости удалиться
            pair.current.deleteLater()
        } else if (pair.type==NEW) {
            //
            // Самый сложный к пониманию сегмент кода. В этом блоке мы обрабатываем
            // потомков текущего элемента, пропуская 
            //
            if (parents.length()==0) {
                // Первый элемент на добавление. Заносим в список предполагаемых родителей.
                parents.append(pair.new);
                // Обрабатываем только от сюда
                processChild(merged, pair.new, pair.newIndex);
            } else {
                if (pair.new.parent()!=parents.last()) {
                    // Родитель не совпал, идем выше по списку родителей
                    found=false;
                    while (parents.length()!=1) {
                        parents.removeLast();
                        if (pair.new.parent()==parents.last()) {
                            // Родитель найден, выходим из цикла
                            found=true;
                            break;
                        }
                        // Это не родитель. Идем дальше пока не переберем всех.
                    }
                    // Сюда мы попадаем как с родителем, так и без. Делаем проверку
                    if (!found) {
                        // Родитель не найден. Откатываем итератор на одну позицию назад
                        // чтобы выполнился блок кода if (parent.length()==0) ...
                        parents.removeLast();
                        iter--;
                        continue;
                    }
                } else {
                    // Родители совпали. Всё равно заносим как потенциально способную быть
                    // родителем в список родителей.
                    parents.append(current);
                    continue;
                }
            }
        } else {
            abort() // на случай обновления с новым типом изменения
        }
    }
}
```

И так, перейдем к функции **processChild()**. Если функция **apply()** находит потенциального родителя и движется направо, пока не закончатся его потомки (с поправкой на вложенность), то эта функция движется по списку изменений налево в поисках родителя или соседа элемента, переданного ей в параметры. 

Simplified js-like code
```
//                          
//         a          a     
//       /   \       /      
//      b     c     b       
//                   \      
//                    c     
//                          
//  После перевода в строковое представление c может быть как
//  потомком b, так и a. Метод **processChild()** решает эту проблему.
//
//  a -> b -> c
//
//  Так же, потомков может быть несколько. Или они могут быть вложенными.
//  Потомок может быть первым ребенком родителя.
//

void processChildprocessChild(megred, itemToAdd, index); {
    // Прошли влево на один элемент и проверяем, является ли он соседствующим
    if (tryInsertAfterChild(merged,itemToAdd,index)) {
        return;
    // Сосед не найден. Идем влево до края и проверяем, первый ли мы потомок
    } else if (tryAppendChild(merged,itemToAdd,index)) {
        return;
    // Это корневая нода. Добавляем в потомки напрямую компоненту
    } else {
        this->appendChild(itemToAdd);
    }
}

//
//     a
//   / | \
//  b  c  d
//
//  Элементы b, c, d - соседи, так как оба дети a. 
//
//   - Если c это новый элемент, то, чтобы привести древо 
//     к каноничному виду, нам нужно вставить его **перед** b
//
//   - Если b это новый элемент, то, чтобы привести древо,
//     на нужно добавить его к a
//

void tryInsertAfterChild(megred, itemToAdd, index) {
    // берем элемент слева
    index--;
    if (merged[index].parent==itemToAdd.parent) {
        // родители совпали - это сосед. Добавляем сразу после по указателю
        merged[index].parent->insertAfterChild(
            merged[index].node,
            itemToAdd
        );
        return true;
    } else {
        return false;
    }
}


void tryAppendChild(megred, itemToAdd, index) {
    // идем налево и ищем родителя
    for (int i=index;i>=0;i--) {
        if (itemToAdd.parent()==merged[i]) {
            // Это родитель. Добавляем.
            merged[i]->appendChild(itemToAdd);
            return true;
        }
    }
    // родитель не найден.
    return false;
}
```

### Потокобезопасность
Цикл событий JavaScript интерпретатора запускается в потоке, отличном от основного потока приложения. Это сделано для разделения задач по просчету изменений древа (описано выше) и компоновки элементов (см flex layout). Однако, библиотека Qt не умеет рисовать пользовательский интерфейс в [потоке](https://doc.qt.io/qt-5/thread-basics.html#gui-thread-and-worker-thread) отличном от базового потока приложения. 

Объект приобретает поток по месту создания оператором new. Поэтому, было решено промаппить  **элементы** пользовательского интерфейса в **ноды** JavaScript через сигналы и слоты для передачи функциональности insert, append, delete, new в одну сторону через механизм [сигналов и слотов](https://doc.qt.io/archives/qt-4.8/threads-qobject.html#signals-and-slots-across-threads).

Simplified js-like code
```
// |                           |                                |
// |         JS thread         |         QML gui thread         |
// |           (Node)          |            (Element)           |
// |                           |                                |
// |  SIGNAL insertAfterChild---->SLOT insertAfterChildHandler  |
// |                           |                                |
// |    SIGNAL appendChild--------->SLOT appendChildHandler     |
// |                           |                                |
// |    SIGNAL deleteLater---------->SLOT diffDeleteHandler     |
// |                           |                                |
```

Некоторые сигналы и слоты ноды и элемента промаплены "в обе стороны". Например, если удаление ноды приведет к удалению элемента (diff обновление древа), то удаление элемента приведет к удалению ноды (очистка мусора при закрытии окна).

### Контекст исполнения функций в свойствах элемента.
Мы не можем запустить JavaScript функцию из QML потока. Кроме того, у функций, переданных в props элементу, разнится контекст исполнения зависимо от родительского компонента. Для исполнения функции мы поставляем её в цикл событий JS интерпретатора через механизм сигналов и слотов. Контекст исполнения функции задается компонентом с использованием Node::updateContext(). При этом, при рассмотрении компонента как элемента, он обновляет контекст исполнения функций в своих параметрах на вышестоящий компонент, но ставит свой контекст дочерним элементам.

Simplified js-like code
```
//
//                component1
//               /          \
//          element1       component2
//         context: c1     context: c1
//           /                  \
//      element2                element3
//    context: c1            context: **c2**
//
```

### Ожидание окончания рендеринга

~~Я хочу сыграть с твоим фреймворком в инкрементальную игру~~

Чтобы просчитать diff изменения, нам нужно получить полностью сформированное как древо нод, так и элементов. Для этого у фреймворка есть специальный [синглет](http://cpp-reference.ru/patterns/creational-patterns/singleton/) DiffCounter, реализующий методы bool DiffCounter::tryIncrementCounter(), void DiffCounter::decrementCounter, bool DiffCounter::changesResolved(). Счетчик увеличевается в insert, append, delete на стороне ноды и уменьшается на стороне элемента. Метод changesResolved() возвращает true, если счетчик равен нулю. Методы этого синглета потокобезопасные. Ниже в псевдокоде представлен сегмент реализации setState у ноды компонента


C#-like sometimes (out, array declaration syntax) code
```
// state - аргумент  функции this.setState() 
// scheduleTimer - поле компонента, хранящее таймер, реализующий
// отложенное обновление

void setState(JSValue state) {
    if (!DiffCounter::instance()->changesResolved()) {
        // старый таймер отменяется, даже если не сработал
        scheduleTimer.stop();
        scheduleTimer.free();    
        // создаем новый таймер. в лямбда-выражение на срабатывание передаем state
        scheduleTimer=new Timer();
        connect(scheduleTimer, &QTimer::timeout, [this,state]() {
            setState(state);
        });
        // срабатывает один раз
        timer.singleShot(50);
    } else {
        // применение нового state (diff рендеринг)
        ...
    }
}
```

Таким образом, если фреймворк не успел применить старое изменение, но получил запрос на применение ещё нескольких, применено будет только последнее. Это очень полезно, если прикладной программист решил создать [инкрементальную игру](https://ru.wikipedia.org/wiki/Инкрементальная_игра). Результат работы будет примерно такой:

Simplified js-like code
```
// |                      |                       |
// | Очередь на рендеринг | Применение рендеринга |
// |                      |                       |
// |        state1        |        state1         |
// |        state2        |         занят         |
// |        state3        |    не прошло 50 мс    |
// |        state4        |    не прошло 50 мс    |
// |        state5        |    не прошло 50 мс    |
// |        state6        |        state6         |
// |                      |                       |
```

### Создание элемента(qml thread) из ноды(js thread)
Созданием элементов из нод занимается класс Manager. В своей реализации он содержит рекурсивную функцию, создающую элементы используя свойство ноды type. Именно поэтому мы пропускаем дочерние элементы новых нод при diff рендеринге - при создании своего родителя они уже промаплены в gui поток. Manager выбрасывает сигнал closed() при закрытии окна, снимая блокировку на выход из цикла событий JavaScript интерпретатора. Если нет блокировки и цикл событий пуст (нет таймеров, выполняемых функций и тд.), то приложение завершается.

### Синхронные диалоговые окна
Как было описано выше, мы не можем рисовать виджеты или окна напрямую из потока JavaScript интерпретатора. Как следствие - для создания синхронного диалога необходимо заблокировать окна и ожидать ввод на стороне QML, опрашивать наличие результата у QML в потоке JavaScript.

Диалоговые окна наследуют от базового класса Dialog. Это шаблонный класс (шаблон обозначает опрашиваемое диалогом значение), реализующий ожидание результата методом Dialog::exec() (метод создает подцикл событий, обеспечивающий работу сигналов и слотов для межпоточного взаимодействия при блокировке основного цикла JavaScript потока). Абстрактный метод Dialog::show() определяется в наследнике Dialog и вызывается из QML потока для отрисовки окна с полем ввода. По факту ввода диалоговое окно выбрасывает сигнал, который прерывает подцикл событий и разблокирует основной цикл JavaScript интерпретатора.
