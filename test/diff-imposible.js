function Example(props) {
    console.log(JSON.stringify({params:props}));
    this.state = {
        text: "0"
    };
}

Example.prototype.render = function () {
    console.log(JSON.stringify({props:this.props}));
    return  Quite.createElement("Rectangle",{paddingTop: 10, paddingLeft: 10},
            Quite.createElement("Rectangle",{height: 75, width: 75, color: "red", marginRight: 10}),
            Quite.createElement("Rectangle",{height: 75, width: 75, color: "green", marginRight: 10}),
            Quite.createElement("Rectangle",{height: 75, width: 75, color: "blue", marginRight: 10}),
            Quite.createElement("Button", {
            text: this.state.text,
            height: 75, 
            width: 150,
            onClick: function() { 
                console.log(JSON.stringify({state:this.state}))
                this.setState({ text: parseInt(this.state.text)+1 });
            }
    }));
}

function test() {
    return  Quite.createElement("Window", null,
        Quite.createElement(Example, {title: "Example"})
    );
}

Quite.render(test());

