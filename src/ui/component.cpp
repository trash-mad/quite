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
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

FlexNode *Component::buildFlexTree() {
    qDebug() << "Component buildFlexTree";
    QLinkedList<Element*> child=getChild();
    QLinkedList<Element*>::iterator iter;
    layout->clearChild();
    for (iter=child.begin();iter!=child.end();iter++) {
        Element* item = *iter;
        item->getLayout()->initNode();
        item->getLayout()->stretchParent();
        layout->appendChild(item->buildFlexTree());
    }
    return layout;
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
