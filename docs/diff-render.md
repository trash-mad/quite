
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
    Quite.createElement("Window",{alignItems:"center",justifyContent:"center}
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