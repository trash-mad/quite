function Example(props) {
    console.log("Example props: "+props);
    this.state = {
        text: "initial text"
    };
}

Example.prototype.render = function (props, state) {
    return Quite.createElement("Window", null, 
        Quite.createElement("Button", {
            text: 123,
            onClicked: function () { return this.setState({ text: 123 }); }
        })
    );
}

function test() {
    console.log("QuiteJS setState test");
    var example = new Example();
    console.log("Render: " + example.render);
    return Quite.createElement(Example, null);
}

Quite.render(test());
