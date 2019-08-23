import QtQuick 2.0

Item {
    property alias color: rectangle.color
    height: 100
    width: 100
    Rectangle {
        id: rectangle
        anchors.fill: parent
    }
}
