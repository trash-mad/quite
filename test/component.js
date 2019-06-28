
class Element {
    constructor(props){
        console.log(props);
        this.state = {
            text: "initial text"
        }
        this.render = this.render.bind(this);
    }
    render(props, state) {
        return (
            <Button
                onClicked={()=>this.setState("omg")}
                text={state.text} />
        );
    }
}

function test() {
    return (
        Quite.createElement("Window", null,
            Quite.createElement(Element, null)
        )
    );
}

Quite.render(test());
