import QtQuick.Controls 2.4
import QtQuick 2.0

import ConsoleProvider 1.0

Item {
    property alias text: button.text
    Button {
        id: button
        anchors.fill: parent
        onClicked: {
            Console.log("qml button clicked")
            Context.onClick()
        }
    }
}
