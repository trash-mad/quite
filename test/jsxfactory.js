function test() {
    return (
        Quite.createElement("Window", null,
            Quite.createElement("Rectangle", { color: "green" })
        )
    );
}

Quite.render(test());
