function Example(props) {
    console.log(JSON.stringify({params:props}));
    this.state = {
        text: "0"
    };
}

Example.prototype.render = function () {
    console.log(JSON.stringify({props:this.props}));
    return Quite.createElement("Button", {
        text: this.state.text,
        onClick: function() { 
            console.log(JSON.stringify({state:this.state}))
            this.setState({ text: parseInt(this.state.text)+1 });
        }
    });
}

function test() {
    return  Quite.createElement("Window", {alignItems:"center",justifyContent:"center"},
        Quite.createElement(Example, {title: "Example",minHeight:75, minWidth: 150})
    );
}

Quite.render(test());

