import QtQuick.Controls 2.5
import QtQuick 2.0

Item {
    id: item
    property bool checked: false
    property alias text: checkbox.text
    CheckBox {
        id: checkbox
        anchors.fill: parent
        checkState: item.checked?Qt.Checked:Qt.Unchecked;
        onCheckStateChanged: Context.onCheck(checkState===Qt.Checked)
    }
}
