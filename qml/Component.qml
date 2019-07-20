import QtQuick 2.10

Item {
    id: item
    anchors.fill: parent

    function resize() {
        if (item.children.length === 1) {
            item.children[0].x = item.x
            item.children[0].y = item.y
            item.children[0].width = item.width
            item.children[0].height = item.height
            return true
        } else {
            return false
        }
    }

    onHeightChanged: resize();
    onWidthChanged: resize();
    onChildrenChanged: {
        if (item.children.length > 1) {
            console.log("Component.qml too many child")
        } else {
            resize()
        }
    }
}
