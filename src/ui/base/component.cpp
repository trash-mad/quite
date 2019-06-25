#include "component.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Component::Component(Node* node)
  : QObject(nullptr) {
    qDebug() << "Component ctor";

    connect(
        node,
        SIGNAL(childChanged(QLinkedList<Node*>)),
        this,
        SLOT(childChangedHandler(QLinkedList<Node*>))
    );

    connect(
        node,
        SIGNAL(propsChanged(QMap<QString,QVariant>)),
        this,
        SLOT(propsChangedHandler(QMap<QString,QVariant>))
    );
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

QLinkedList<Component *> Component::getChilds() const {
    return child;
}

/*---------------------------------------------------------------------------*/

QMap<QString, QVariant> Component::getProps() const {
    return props;
}

/*---------------------------------------------------------------------------*/

QQuickItem *Component::getItem() const {
    return item;
}

/*---------------------------------------------------------------------------*/

void Component::childChangedHandler(QLinkedList<Node*> child) {
    qDebug() << "Component childChangedHandler";

    QLinkedList<Component*>::iterator i;
    for (i = this->child.begin(); i != this->child.end(); i++){
        Component* component = (*i);
        component->deleteLater();
    }

    emit updateSubtree(child);
}

/*---------------------------------------------------------------------------*/

void Component::propsChangedHandler(QMap<QString, QVariant> props) {
    qDebug() << "Component propsChangedHandler";
    this->props = props;
    propsChanged();
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
