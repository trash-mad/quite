import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick 2.0

Item {
    id: item
    property string title: "Title"

    ToolBar {
        id: bar
        RowLayout {
            anchors.fill: parent
            Label {
                text: item.title
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }
}
