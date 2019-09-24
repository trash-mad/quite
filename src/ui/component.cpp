#include "component.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Component::Component(ComponentNode* node, QQmlEngine* engine, Element* parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Component.qml")),
        node,
        engine,
        parent
    ) {
    qDebug() << "Component ctor";
    connect(
        node,
        SIGNAL(renderSubtree(Node*)),
        this,
        SLOT(renderSubtreeHandler(Node*))
    );
    connect(
        node,
        SIGNAL(renderDiff()),
        this,
        SLOT(updateLayout())
    );
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

FlexNode *Component::buildFlexTree(bool fill) {
    Q_UNUSED(fill)
    layout = new FlexNode(getItem());
    QLinkedList<Element*> child=getChild();
    QLinkedList<Element*>::iterator iter;
    if (child.count()==1) {
        iter=iter=child.begin();
        layout->appendChild((*iter)->buildFlexTree(true));
        (*iter)->startLayoutUpdate();
    } else {
        qCritical() << "Component buildFlexTree not one child";
    }
    return layout;
}

/*---------------------------------------------------------------------------*/

void Component::updateLayoutNow() {
    qDebug() << "Component updateLayoutNow";
    auto h=getItem()->height();
    auto w=getItem()->width();
    Element::updateLayoutNow(
        static_cast<int>(h),
        static_cast<int>(w)
    );
}

/*---------------------------------------------------------------------------*/

void Component::renderSubtreeHandler(Node *child) {
    if (!diffImposible) {
        diffImposible=true;
        qInfo()
            << "Diff rendering is impossible."
            << "The sequence contains a list of items without a key prop";
    }
    emit renderSubtree(child);
}

/*****************************************************************************/

} // namespace Ui
} // namespa Quite
