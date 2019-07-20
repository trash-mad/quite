function Example(props) {
    console.log(JSON.stringify({params:props}));
    this.state = {
        text: "0"
    };
}

Example.prototype.render = function () {
    console.log(JSON.stringify({props:this.props}));
    return Quite.createElement("Rectangle", { 
            height: 100, 
            width: 100+parseInt(this.state.text), 
        }, Quite.createElement("Rectangle", { 
                height: 125, 
                width: 100-parseInt(this.state.text), 
                color: "blue"
            },Quite.createElement("Rectangle", { 
                height: 125, 
                width: 100-parseInt(this.state.text), 
                color: "blue"
            }),Quite.createElement("Rectangle", { 
                height: 125, 
                width: 100-parseInt(this.state.text), 
                color: "blue"
            }),Quite.createElement("Rectangle", { 
                height: 125, 
                width: 100-parseInt(this.state.text), 
                color: "blue"
            }),Quite.createElement("Rectangle", { 
                height: 125, 
                width: 100-parseInt(this.state.text), 
                color: "blue"
            }),Quite.createElement("Rectangle", { 
                height: 125, 
                width: 100-parseInt(this.state.text), 
                color: "blue"
            })), Quite.createElement("Button", {
                    text: this.state.text,
                    onClicked: function() { 
                        console.log(JSON.stringify({state:this.state}))
                        this.setState({ text: parseInt(this.state.text)+1 });
                        gc();
                    }
                })
        );
}

function test() {
    return  Quite.createElement("Window", null,
        Quite.createElement(Example, {title: "Example"})
    );
}

Quite.render(test());

