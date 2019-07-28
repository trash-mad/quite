import QtQuick.Controls 2.4

Button {
    id: button
    text: "Button"
    onClicked: {
        //Quite.invoke(button, "clicked");
        console.log(123);
        onClick();
    }
}
