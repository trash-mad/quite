function SampleComponent(props) {
    console.log("SampleComponent ctor");
    this.state={
        rects:[]
    }
}

SampleComponent.prototype.render=function() {
    return Quite.createElement("Rectangle", {color: "yellow", flexDirection: "column", marginTop: 5, marginLeft: 5},
        Quite.createElement("Rectangle", {height: 55, color: "whitesmoke", flexDirection: "row", minHeight: 50, paddingTop: 5},
            Quite.createElement("Button", {text: "Add rect", height: 50, width: 125, marginRight:5, onClick: this.addRect}),
            Quite.createElement("Button", {text: "Remove rect", height: 50, width: 125, onClick: this.removeRect}),
        ), 
        Quite.createElement("Rectangle", {color: "red", flexDirection: "column", marginTop: 5, flexWrap: "wrap", minHeight: 180, minWidth: 180},
            this.state.rects.map((_, index)=>Quite.createElement("Rectangle", {
                        key: index,
                        height: 50, 
                        width: 50, 
                        color: "green", 
                        margin: 5
            }
            ))
        ),
    );
}

SampleComponent.prototype.addRect=function() {
    console.log("addRect")
    this.setState({
        rects:this.state.rects.concat([1])
    })
}

SampleComponent.prototype.removeRect=function() {
    console.log("removeRect")
    const rects=this.state.rects.reverse().slice(1).reverse();
    console.log(JSON.stringify(rects));
    this.setState({rects})
}

function test() {
    return  Quite.createElement("Window", null,
        Quite.createElement(SampleComponent, {heightPercent: 100, widthPercent: 100})
    );
}

Quite.render(test());