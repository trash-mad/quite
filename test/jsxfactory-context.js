function ClassOne() {
    console.log("ClassOne ctor");
}

ClassOne.prototype.render = function () {
    console.log("ClassTwo render")
    return Quite.createElement("Button", {
        text: "Test",
        onClicked: function() { 
            this.props.callBack();
        }
    });
}

function ClassTwo() {
    console.log("ClassTwo ctor");
}

ClassTwo.prototype.test = function () {
    console.log("OMG)))");
}

ClassTwo.prototype.render = function () {
    console.log("ClassTwo render");
    return Quite.createElement(ClassOne, {callBack: this.test})
}


function test() {
    return  Quite.createElement("Window", null,
        Quite.createElement(ClassTwo, {title: "Example"})
    );
}

Quite.render(test());

