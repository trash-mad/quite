function SampleComponent(props) {
    this.state={
        rects:[]
    }
}

function getColorByIndex(index) {
    index=index%10;
    index=index>6?index-4:index;
    switch (index) {
        case 0:
            return "red";
        case 1:
            return "orange";
        case 2:
            return "yellow";
        case 3:
            return "green";
        case 4:
            return "skyblue";
        case 5:
            return "blue";
        case 6:
            return "violet";
    }
}

SampleComponent.prototype.render=function() {
    return Quite.createElement("Rectangle", {
            color: "whitesmoke",
            flexDirection: "column", 
            padding: 15
        },
        Quite.createElement("Rectangle", {
                color: "transparent", 
                flexDirection: "row", 
                height: 50
            },
            Quite.createElement("Button", {
                text: "Add two rects", 
                height: 50, 
                width: 125, 
                marginRight:5, 
                onClick: this.addRect
            }),
            Quite.createElement("Button", {
                text: "Remove one rect", 
                height: 50, width: 125, 
                onClick: this.removeRect
            }),
        ), 
        Quite.createElement("ScrollViewer", {
                flexDirection: "column", 
                marginTop: 5, 
                flexWrap: "wrap", 
                minHeight: 360, 
                minWidth: 360
            },
            this.state.rects.map((_, index)=>Quite.createElement("Rectangle", {
                key: index,
                height: 50, 
                width: 50, 
                color: getColorByIndex(index), 
                margin: 5
            }))
        ),
    );
}

SampleComponent.prototype.addRect=function() {
    this.setState({
        rects:this.state.rects.concat([1, 1])
    })
}

SampleComponent.prototype.removeRect=function() {
    const rects=this.state.rects
        .reverse()
        .slice(1)
        .reverse();
    this.setState({rects})
}

function test() {
    return  Quite.createElement("Window", null,
        Quite.createElement("ScrollViewer",{
                heightPercent: 100, 
                widthPercent: 100,
                alignItems: "center",
                justifyContent: "center",
            },
            Quite.createElement(SampleComponent, {
                minHeight: 445,
                minWidth: 395
            })
        )
    );
}

Quite.render(test());