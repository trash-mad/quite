#include "component.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Component::Component(ComponentNode* node, QQmlEngine *engine, Element *parent)
  : Element(node, engine, parent) {
    qDebug() << "Component ctor";
    item = new QQuickItem();
    instance = node->getInstance();
    connect(
        node,
        SIGNAL(childChanged(Node*)),
        this,
        SLOT(requireSubtree(Node*))
    );
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

void Component::receiveSubtree(Element* child) {
    qDebug() << "Component receiveSubtree";
    this->child.append(child);
    childChanged();
}

/*---------------------------------------------------------------------------*/

void Component::requireSubtree(Node *child) {
    qDebug() << "Component emitUpdateSubtree";
    QLinkedList<Element*>::iterator i;
    for (i = this->child.begin(); i != this->child.end(); i++){
        Element* element = (*i);
        element->deleteLater();
    }
    this->child.erase(this->child.begin(), this->child.end());
    emit updateSubtree(child, this);
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
