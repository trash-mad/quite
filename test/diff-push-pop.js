
function SampleComponent(props) {
    console.log("SampleComponent ctor");
    this.state={
        rects:[]
    }
}

SampleComponent.prototype.render=function() {
    return Quite.createElement("Rectangle", {color: "whitesmoke", flexDirection: "column", marginTop: 5, marginLeft: 5},
        Quite.createElement("Rectangle", {color: "whitesmoke", flexDirection: "row", minHight: 50, paddingTop: 5},
            Quite.createElement("Button", {text: "Add rect", height: 50, width: 125, marginRight:5, onClick: this.addRect}),
            Quite.createElement("Button", {text: "Remove rect", height: 50, width: 125, onClick: this.removeRect}),
        ), 
        Quite.createElement("Rectangle", {color: "whitesmoke", flexDirection: "row", paddingTop: 5},
            this.state.rects.map((_, index)=>Quite.createElement("Rectangle", {
                        key: index+1,
                        height: 50, 
                        width: 50, 
                        color: "cyan", 
                        marginRight: 5
                    },
                Quite.createElement("Rectangle", {key:59,minHeight:15, minWidth:15, color:"red"},
                    Quite.createElement("Rectangle", {key:60,minHeight:15, minWidth:15, color:"red"}),
                    Quite.createElement("Rectangle", {key:61,minHeight:15, minWidth:15, color:"red"}),
                    Quite.createElement("Rectangle", {key:62,minHeight:15, minWidth:15, color:"red"})
                ),
                Quite.createElement("Rectangle", {key: 88, minHeight:63, minWidth:15, color:"red"})
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
        Quite.createElement(SampleComponent, {minWidth: 250})
    );
}

Quite.render(test());