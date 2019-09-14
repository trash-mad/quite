import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: item
    ScrollView {
        id: view
        anchors.fill: parent
        contentWidth: content.childrenRect.width
        contentHeight: content.childrenRect.height
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ScrollBar.horizontal.interactive: true
        ScrollBar.vertical.interactive: true
        clip: true
        Item { id: content }
    }
    onChildrenChanged: {
        const length=item.children.length;
        if (length===1) {
            return;
        } else {
            item.children[length-1].parent=content;
        }
    }
}


