import QtQuick.Controls 2.5
import QtQuick 2.0

Item {
    id: item
    property var items: []
    property string placeholder: "Empty selection"
    property alias currentIndex: box.currentIndex
    ComboBox {
        id: box
        anchors.fill: parent
        currentIndex: 0
        model: Array.isArray(item.items)?[item.placeholder].concat(item.items.map(i=>i.toString())):[];
        onCurrentIndexChanged: {
            const index = currentIndex-1;
            if (box.currentIndex===-1) {
                return;
            } else {
                onElementSelectionChanged(index);
            }
        }
    }
}
