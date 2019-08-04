function SampleComponent() {
    this.state={
        arr: [1,2,3,4],
        total: 0
    }
}

SampleComponent.prototype.render = function () {
    return Quite.createElement("Rectangle", { color: "whitesmoke", width: 700, height:250 },
        Quite.createElement("Button", { 
            text: "Add rect",
            x:5,
            key: 1,
            y:5,
            width: 140,
            onClick: function() {
                console.log("click"); 
                const state = this.state;
                state.total++;
                if (state.arr.length==4) {
                    state.arr.pop();
                } else {
                    state.arr.push(state.total);
                }
                this.setState(state);
            }
        }),
        this.state.arr.map((item, index)=>Quite.createElement("Rectangle", {
            x: (index*50)+5,
            y: 50,
            key: item,
            color: "cyan",
            height: 45,
            width: 45
        }))
    );
}

function test() {
    return  Quite.createElement("Window", null,
        Quite.createElement(SampleComponent, null)
    );
}

Quite.render(test());

