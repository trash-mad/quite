import QtQuick.Controls 2.5
import QtQuick 2.0

import ConsoleProvider 1.0

Item {
    id: item

    /*
     * INFO: при центровке элементов yoga может выставлять отрицательные
     * координаты x и y. ScrollViewer не умеет работать с такими,
     * поэтому мы сдвигаем точку отсчета системы до (0,0)
     * applyBasisFix
     */

    ScrollView {
        id: view
        anchors.fill: parent
        contentWidth: content.childrenRect.width
        contentHeight: content.childrenRect.height
        ScrollBar.horizontal.policy: ScrollBar.AsNeeded
        ScrollBar.vertical.policy: ScrollBar.AsNeeded
        property int oldHeight: -1
        property int oldWidth: -1
        clip: true
        Item {
            id: content
            property int dx: 0
            property int dy: 0
            onChildrenRectChanged: { applyBasisFix(); }
        }
    }

    function checkHeightChanged() {
        if (item.height!=view.oldHeight) {
            view.oldHeight=item.height;
            content.dy=0;
            return true;
        } else {
            return false;
        }
    }

    function checkWidthChanged() {
        if (item.width!=view.oldWidth) {
            view.oldWidth=item.width;
            content.dx=0;
            return true;
        } else {
            return false;
        }
    }

    function applyBasisFix() {
        const length=content.children.length;
        let dyChanged=!checkHeightChanged();
        let dxChanged=!checkWidthChanged();
        for (let i=0;i!==length;i++) {
            const child=content.children[i];
            if (child.x<content.dx) {
                content.x=Math.abs(child.x);
                content.dx=child.x;
                dxChanged=true;
            }
            if (child.y<content.dy) {
                content.y=Math.abs(child.y);
                content.dy=child.y;
                dyChanged=true;
            }
        }
        content.x=dxChanged?content.x:0;
        content.y=dyChanged?content.y:0;
        Console.debug("ScrollViewer x:",content.x," y:",content.y);
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


