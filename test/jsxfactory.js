function test() {
    return (
        Quite.createElement("Window", null,
            Quite.createElement("Text", { text: "test" })
        )
    );
}

Quite.render(test());
