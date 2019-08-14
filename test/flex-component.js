function TestClass(props) {
    console.log("TestClass ctor")
}

TestClass.prototype.render = function() {
    return Quite.createElement("Rectangle", {alignItems:"center",justifyContent:"center", minHeight: 50, minWidth: 50},
        Quite.createElement("Rectangle", {alignItems:"center",justifyContent:"center", minHeight: 10, minWidth: 10, color: "blue"})
    );
}


function test() {
    return  Quite.createElement("Window", {alignItems:"center",justifyContent:"center"},
        Quite.createElement(TestClass,{minHeight:77,minWidth:77})
    );
}

Quite.render(test());

