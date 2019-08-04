#include "element.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Element::Element(
    QUrl uri,
    Node *node,
    QQmlEngine *engine,
    Element *parent
) : QObject(parent) {
    qDebug() << "Element ctor";
    this->type=node->getEnumType();
    connect(node, SIGNAL(destroyed()), this, SLOT(deleteLater()));
    connect(
        node,
        SIGNAL(propsChanged(QMap<QString,QVariant>,bool)),
        this,
        SLOT(propsChangedHandler(QMap<QString,QVariant>,bool))
    );
    connect(
        node,
        SIGNAL(childInsertedAfter(Node*, Node*)),
        this,
        SLOT(childInsertedAfterHandler(Node*, Node*))
    );
    connect(
        node,
        SIGNAL(childAppended(Node*)),
        this,
        SLOT(childAppendedHandler(Node*))
    );
    connect(
        node,
        SIGNAL(diffDelete()),
        this,
        SLOT(diffDeleteHandler())
    );

    context=new QQmlContext(engine->rootContext(),this);
    context->setContextObject(this);

    QQmlComponent component(engine, uri);
    QObject* object=component.beginCreate(context);
    component.completeCreate();

    WindowComponent* window = qobject_cast<WindowComponent*>(object);
    if (window==nullptr) {
        item=qobject_cast<QQuickItem*>(object);
    } else {
        item=window->contentItem();
        connect(
            window,
            SIGNAL(closed()),
            this,
            SIGNAL(windowClosed())
        );
    }
}

/*---------------------------------------------------------------------------*/

Element::~Element() {
    qDebug() << "Element dtor";
    item->deleteLater();
}

/*---------------------------------------------------------------------------*/

void Element::onClick() {
    qCritical() << "Element default click handler";
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

void Element::propsChangedHandler(
    QMap<QString, QVariant> commitProps,
    bool merge
) {
    qDebug() << "Element propsChangedHandler";
    this->props=commitProps;
    if (merge) {
        propsChanged();
        RenderSynchronizer::instance()->decrementCounter(
            QString("Merge %1").arg(QVariant(getType()).toString())
        );
    } else {
        propsChanged();
    }
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

/*---------------------------------------------------------------------------*/

void Element::diffDeleteHandler() {
    qDebug() << "Element diffDeleteHandler";
    item->setParentItem(nullptr);
    RenderSynchronizer::instance()->decrementCounter(
        QString("Delete %1").arg(QVariant(getType()).toString()
    ));
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
