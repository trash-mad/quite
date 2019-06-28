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

QQuickItem* Component::getItem() const {
    return item;
}

/*---------------------------------------------------------------------------*/

void Component::childChanged(QLinkedList<Component *> child) {
    qDebug() << "Component default childChanged";
    this->child = child;
    QLinkedList<Component*>::iterator i;
    for (i=child.begin(); i!=child.end();i++) {
        Component* component = (*i);
        component->getItem()->setParentItem(item);
    }
}

/*---------------------------------------------------------------------------*/

QMap<QString, QVariant> Component::propsChanged(
    QMap<QString, QJSValue> props
) {
    qDebug() << "Component default propsChanged";
    QMap<QString, QVariant> tmp;
    QMap<QString, QJSValue>::iterator i;
    for(i = props.begin(); i!= props.end(); i++) {
        QString name = i.key();
        QVariant value = i.value().toVariant();
        item->setProperty(name.toStdString().c_str(),value);
        tmp.insert(name, value);
    }
    return tmp;
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

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
