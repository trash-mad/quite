import QtQuick.Controls 2.5
import QtQuick 2.0

Item {
    id: item
    property alias text: label.text
    Label {
        id: label
        anchors.fill: parent
    }
}
