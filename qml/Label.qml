import QtQuick.Controls 2.5
import QtQuick 2.12


Item {
    id: item
    property alias text: label.text
    Text {
        id: label
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 16
        anchors.fill: parent
    }
}
