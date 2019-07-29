function ClassOne() {
    console.log("ClassOne ctor");
}

ClassOne.prototype.render = function () {
    console.log("ClassTwo render")
    return Quite.createElement("Button", {
        text: "Test",
        onClick: function() { 
            console.log("Props in ClassOne: "+JSON.stringify(this.props));
            this.props.callBack();
        }
    });
}

function ClassTwo() {
    console.log("ClassTwo ctor");
    this.test=this.test.bind(this);
}

ClassTwo.prototype.test = function () {
    console.log("Props in ClassTwo: "+JSON.stringify(this.props));
}

ClassTwo.prototype.render = function () {
    console.log("ClassTwo render");
    return Quite.createElement(ClassOne, {className:"ClassOne", callBack: this.test})
}


function test() {
    return  Quite.createElement("Window", null,
        Quite.createElement(ClassTwo, {className: "ClassTwo"})
    );
}

Quite.render(test());

