import QtQuick 2.0

Item {
    id: item
    property alias color: rectangle.color
    Rectangle {
        id: rectangle
        anchors.fill: item
    }
}
