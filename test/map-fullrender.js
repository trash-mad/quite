function SampleComponent() {
    this.state={
        arr: [1,2,3],
        count: 3
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
                const state=this.state;
                state.arr.push(state.count+1)
                this.setState({arr:state.arr,count:state.count+1});
            }
        }),
        Quite.createElement("Button", { 
            text: "Remove rect",
            x: 150,
            y: 5,
            width: 140,
            onClick: function() { 
                console.log("click");
                const state=this.state;
                state.arr.pop();
                this.setState({arr:state.arr,count:state.count-1});
            }
        }),
        this.state.arr.map((item, index)=>Quite.createElement("Rectangle", {
            x: (index*50)+5,
            y: 50,
            /*key: item,*/
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

