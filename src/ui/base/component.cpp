#include "component.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Component::Component(Node* node, QQmlEngine* engine, Component* parent)
  : QObject(parent) {
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

    this->engine = engine;
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

void Component::childChanged(QLinkedList<Component *> child) {
    qDebug() << "Component default childChanged";
    QLinkedList<Component*>::iterator i;
    for (i=child.begin(); i!=child.end();i++) {
        Component* component = (*i);
        component->getItem()->setParentItem(item);
    }
}

/*---------------------------------------------------------------------------*/

void Component::propsChanged(QMap<QString, QVariant> props) {
    qDebug() << "Component default propsChanged";
    QMap<QString, QVariant>::iterator i;
    for(i = props.begin(); i!= props.end(); i++) {
        item->setProperty(i.key().toStdString().c_str(),i.value());
    }
}

/*---------------------------------------------------------------------------*/

void Component::childChangedHandler(QLinkedList<Node*> child) {
    qDebug() << "Component childChangedHandler";

    QLinkedList<Component*>::iterator i;
    for (i = this->child.begin(); i != this->child.end(); i++){
        Component* component = (*i);
        component->deleteLater();
    }
    this->child.erase(this->child.begin(), this->child.end());

    emit updateSubtree(this, child);
}

/*---------------------------------------------------------------------------*/

void Component::propsChangedHandler(QMap<QString, QVariant> props) {
    qDebug() << "Component propsChangedHandler";
    this->props = props;
    propsChanged(props);
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
