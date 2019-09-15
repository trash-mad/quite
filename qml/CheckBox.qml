import QtQuick.Controls 2.5
import QtQuick 2.0

Item {
    id: item
    property bool checked: false
    CheckBox {
        anchors.fill: parent
        checkState: item.checked?Qt.Checked:Qt.Unchecked;
        onCheckStateChanged: onElementCheck(checkState===Qt.Checked)
    }
}
