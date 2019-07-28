#include "element.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Element::Element(
    QString compUri,
    Node *node,
    QQmlEngine *engine,
    Element *parent
) : QObject(parent) {
    qDebug() << "Element ctor";
    this->type=node->getEnumType();
    connect(node, SIGNAL(destroyed()), this, SLOT(deleteLater()));
    QQmlComponent component(engine, compUri);
    //item.beginCreate(engine->rootContext());
    //item.setProperty("element", QVariant::fromValue(this));
    //item.completeCreate();

    QObject* object = component.create();
    QQuickWindow* window = qobject_cast<QQuickWindow*>(object);
    if (window==nullptr) {
        item=qobject_cast<QQuickItem*>(object);
    } else {
        item=window->contentItem();
    }
}

/*---------------------------------------------------------------------------*/

Element::~Element() {
    qDebug() << "Element dtor";
    item->deleteLater();
}

/*---------------------------------------------------------------------------*/

void Element::childInsertAfter(Node *after, Element *child) {
    qDebug() << "Element default childInsertAfter";
    QList<QQuickItem*>::iterator itemIter=this->item->childItems().begin();
    QLinkedList<Element*>::iterator elemIter=this->child.begin();
    while (elemIter!=this->child.end()) {
        Element* item = (*elemIter);
        if (item->getNode()==after) {
            elemIter++;
            itemIter++;
            this->child.insert(elemIter,child);
            this->getItem()->childItems().insert(itemIter,child->getItem());
            connect(
                child,
                SIGNAL(destroyed(QObject*)),
                this,
                SLOT(childDeletedHandler(QObject*))
            );
            return;
        } else {
            elemIter++;
            itemIter++;
        }
    }
    qCritical() << "Element default childInsertAfter child not found";
}

/*---------------------------------------------------------------------------*/

void Element::childAppend(Element *child) {
    qDebug() << "Element default childAppend";
    this->child.append(child);
    child->getItem()->setParentItem(item);
    connect(
        child,
        SIGNAL(destroyed(QObject*)),
        this,
        SLOT(childDeletedHandler(QObject*))
    );
}

/*---------------------------------------------------------------------------*/

void Element::childDeleted(Element *child) {
    qDebug() << "Element default childDeleted";
    this->child.removeOne(child);
}

/*---------------------------------------------------------------------------*/

void Element::childChanged() {
    qDebug() << "Element default childChanged";
    QLinkedList<Element*>::iterator i;
    for (i=child.begin(); i!=child.end();i++) {
        Element* element = (*i);
        element->getItem()->setParentItem(getItem());
        connect(
            element,
            SIGNAL(destroyed(QObject*)),
            this,
            SLOT(childDeletedHandler(QObject*))
        );
    }
}

/*---------------------------------------------------------------------------*/

void Element::propsChanged() {
    qDebug() << "Element default propsChanged";
    QMap<QString, QVariant>::iterator i;
    for(i = props.begin(); i!= props.end(); i++) {
        QString name = i.key();
        QVariant value = i.value();
        item->setProperty(name.toStdString().c_str(), value);
    }
}

/*---------------------------------------------------------------------------*/

QMap<QString, QVariant> Element::getProps() const {
    return props;
}

/*---------------------------------------------------------------------------*/

QLinkedList<Element *> Element::getChild() const {
    return child;
}

/*---------------------------------------------------------------------------*/

QQuickItem *Element::getItem() const {
    return item;
}

/*---------------------------------------------------------------------------*/

NodeType Element::getType() const {
    return type;
}

/*---------------------------------------------------------------------------*/

Node *Element::getNode() const {
    return node;
}

/*---------------------------------------------------------------------------*/

void Element::receiveSubtree(QLinkedList<Element *> child) {
    qDebug() << "Element receiveSubtree";
    this->child=child;
    childChanged();
}

/*---------------------------------------------------------------------------*/

void Element::propsChangedHandler(QMap<QString, QVariant> commitProps) {
    qDebug() << "Element propsChangedHandler";
    this->props=commitProps;
    propsChanged();
}

/*---------------------------------------------------------------------------*/

void Element::childInsertedAfterHandler(Node *after, Node *child) {
    qDebug() << "Element childInsertedAfterHandler";
    emit insertAfterChild(after, child);
}

/*---------------------------------------------------------------------------*/

void Element::childDeletedHandler(QObject* child) {
    qDebug() << "Element childDeletedHandler";
    Element* item = qobject_cast<Element*>(child);
    if (item==nullptr) {
        childDeleted(item);
    } else {
        qCritical() << "Element childDeletedHandler child not Element";
    }
}

/*---------------------------------------------------------------------------*/

void Element::childAppendedHandler(Node *child) {
    qDebug() << "Element childAppendedHandler";
    emit appendChild(child);
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
