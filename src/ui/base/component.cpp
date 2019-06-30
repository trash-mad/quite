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
        SIGNAL(propsChanged(QMap<QString, QJSValue>)),
        this,
        SLOT(propsChangedHandler(QMap<QString, QJSValue>))
    );
    this->engine = engine;
    this->node = node;
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

QLinkedList<Component *> Component::getChild() const {
    return child;
}

/*---------------------------------------------------------------------------*/

QMap<QString, QJSValue> Component::getProps() const {
    return props;
}

/*---------------------------------------------------------------------------*/

Node *Component::getNode() const {
    return node;
}

/*---------------------------------------------------------------------------*/

void Component::silentPropUpdate(QString key, QJSValue value) {
    qDebug() << "Component silentPropUpdate" << key;
    props.insert(key, value);
}

/*---------------------------------------------------------------------------*/

QQuickItem* Component::getItem() const {
    return item;
}

/*---------------------------------------------------------------------------*/

void Component::childChanged() {
    qDebug() << "Component default childChanged";
    QLinkedList<Component *> child = getChild();
    this->child = child;
    QLinkedList<Component*>::iterator i;
    for (i=child.begin(); i!=child.end();i++) {
        Component* component = (*i);
        component->getItem()->setParentItem(item);
    }
}

/*---------------------------------------------------------------------------*/

void Component::propsChanged() {
    qDebug() << "Component default propsChanged";
    QMap<QString, QJSValue> props = getProps();
    QMap<QString, QJSValue>::iterator i;
    for(i = props.begin(); i!= props.end(); i++) {
        QString name = i.key();
        QVariant value = i.value().toVariant();
        item->setProperty(name.toStdString().c_str(),value);
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

void Component::propsChangedHandler(QMap<QString, QJSValue> props) {
    qDebug() << "Component propsChangedHandler";
    this->props = props;
    propsChanged();
    emit propsChangedInvoked();
}

/*---------------------------------------------------------------------------*/

void Component::receiveSubtree(QLinkedList<Component *> child) {
    qDebug() << "Component receiveSubtree";
    this->child = child;
    childChanged();
    emit childChangedInvoked();
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
