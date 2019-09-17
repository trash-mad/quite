import QtQuick 2.0

Item {
    id: item

    property Item _content: ({})
    property string _type: ""

    Component.onCompleted: {
        if (_type==="") {
            console.warn("Invalid ")
        } else {
            _content.parent=item;
        }
    }

    onChildrenChanged: {
        const length=item.children.length;
        item.children[length-1].parent=_content;
    }
}
