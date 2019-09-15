import QtQuick.Controls 2.4
import QtQuick 2.0

Item {
    property alias text: button.text
    Button {
        id: button
        anchors.fill: parent
        onClicked: onElementClick()
    }
}
