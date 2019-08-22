
/*function SampleComponent(props) {
    console.log("SampleComponent ctor");
    this.state={
        rects:[1,1,1]
    }
}

SampleComponent.prototype.render=function() {
    return Quite.createElement("Rectangle", {flexDirection: "rowReverse", color: "white", marginTop: 5, marginLeft: 5},
    Quite.createElement("Rectangle", {height: 55, color: "whitesmoke", minHight: 50, paddingTop: 5},
    Quite.createElement("Button", {text: "Add rect", height: 50, width: 125, marginRight:5, onClick: this.addRect}),
    Quite.createElement("Button", {text: "Remove rect", height: 50, width: 125, onClick: this.removeRect}),
    ),
        Quite.createElement("Rectangle", {color: "whitesmoke", paddingTop: 5},
            this.state.rects.map((_, index)=>Quite.createElement("Rectangle", {
                    key: index+1,
                    height: 50, 
                    width: 50, 
                    color: "cyan", 
                    marginRight: 5
                },
            ))
        ));
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
    return  Quite.createElement("Window", {alignItems: "center", justifyContent: "center"},
        Quite.createElement(SampleComponent, {heightPercent: 10, widthPercent: 10})
    );
}

Quite.render(test());*/

Quite.render(Quite.createElement("Window", {alignItems: "center", justifyContent: "center"},
    Quite.createElement("Rectangle", {flexDirection: "rowReverse", color: "gray", alignItems: "center", justifyContent: "center", height:150, width: 150},
        Quite.createElement("Rectangle", {height:50, width: 50, color: "red"}),
        Quite.createElement("Rectangle", {height:50, width: 50, color: "green"}),
        Quite.createElement("Rectangle", {height:50, width: 50, color: "blue"})
    )
));