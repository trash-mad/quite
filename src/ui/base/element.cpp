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
    connect(
        node,
        SIGNAL(destroyed()),
        this,
        SLOT(deleteLater())
    );
    connect(
        node,
        SIGNAL(propsChanged(QMap<QString,QVariant>,bool)),
        this,
        SLOT(propsChangedHandler(QMap<QString,QVariant>,bool))
    );
    connect(
        node,
        SIGNAL(childInsertedAfterIndex(int, Node*)),
        this,
        SLOT(childInsertedAfterIndexHandler(int, Node*))
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
        SLOT(diffDeleteEmit())
    );

    context=new QQmlContext(engine->rootContext(),this);
    context->setContextObject(this);

    QQmlComponent component(engine, uri);
    QObject* object=component.create(context);

    if (object==nullptr) {
        qCritical() << "Element" << type << "creation failed";
    } else {
        FlexNode::initDefaultProps(object);
        item=qobject_cast<QQuickItem*>(object);
        item->setVisible(false);
    }
}

/*---------------------------------------------------------------------------*/

Element::~Element() {
    qDebug() << "Element dtor";
    item->deleteLater();
}

/*---------------------------------------------------------------------------*/

void Element::onElementClick() {
    qCritical() << "Element default click handler";
}

/*---------------------------------------------------------------------------*/

void Element::onElementCheck(bool enabled) {
    Q_UNUSED(enabled)
    qCritical() << "Element default check handler";
}

/*---------------------------------------------------------------------------*/

void Element::onElementValueChanged(QVariant value) {
    Q_UNUSED(value)
    qCritical() << "Element default valueChanged handler";
}

/*---------------------------------------------------------------------------*/

void Element::childInsertAfterIndex(int index, Element *elem) {
    qDebug() << "Element default childInsertAfter";
    if (index>this->child.count()) {
        qCritical() << "Element default childInsertAfter index out of range";
    } else {
        QLinkedList<Element*>::iterator iter=this->child.begin();
        iter+=index;
        this->child.insert(iter,elem);
        elem->getItem()->setParentItem(this->getItem());
        connect(
            elem,
            SIGNAL(destroyed(QObject*)),
            this,
            SLOT(childDeletedHandler(QObject*))
        );
        connect(
            elem,
            SIGNAL(diffDelete()),
            this,
            SLOT(childDiffDeleteHandler())
        );
        QMetaObject::invokeMethod(this,"updateLayout",Qt::QueuedConnection);
    }
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
    connect(
        child,
        SIGNAL(diffDelete()),
        this,
        SLOT(childDiffDeleteHandler())
    );
    updateLayout();
}

/*---------------------------------------------------------------------------*/

void Element::childDeleted(Element *child) {
    qDebug() << "Element default childDeleted";
    this->child.removeOne(child);
    updateLayout();
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
        connect(
            element,
            SIGNAL(diffDelete()),
            this,
            SLOT(childDiffDeleteHandler())
        );
    }
    updateLayout();
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
        DiffCounter::instance()->decrementCounter();
        updateLayout();
    } else {
        propsChanged();
    }
}

/*---------------------------------------------------------------------------*/

void Element::childInsertedAfterIndexHandler(int index, Node *child) {
    qDebug() << "Element childInsertedAfterHandler";
    emit insertAfterChildIndex(index, child);
}

/*---------------------------------------------------------------------------*/

void Element::childDeletedHandler(QObject* child) {
    qDebug() << "Element childDeletedHandler";
    Element* item = qobject_cast<Element*>(child);
    if (item!=nullptr) {
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

void Element::childDiffDeleteHandler() {
    Element* sender=qobject_cast<Element*>(QObject::sender());
    disconnect(
        sender,
        SIGNAL(destroyed(QObject*)),
        this,
        SLOT(childDeletedHandler(QObject*))
    );
    childDeletedHandler(sender);
    DiffCounter::instance()->decrementCounter();
    updateLayout();
}

/*---------------------------------------------------------------------------*/

void Element::diffDeleteEmit() {
    qDebug() << "Element diffDeleteEmit";
    emit diffDelete();
}

/*---------------------------------------------------------------------------*/

FlexNode *Element::buildFlexTree(bool fill) {
    layout = new FlexNode(getItem(),fill);
    QLinkedList<Element*> child=getChild();
    QLinkedList<Element*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        layout->appendChild((*iter)->buildFlexTree(false));
        /* layout инициализирован, позволяем рисовать */
        (*iter)->startLayoutUpdate();
    }
    return layout;
}

/*---------------------------------------------------------------------------*/

void Element::updateLayout() {
      qDebug() << "Element updateLayout";
      DiffCounter* instance = DiffCounter::instance();
      bool resolved = instance->changesResolved();
      if (!layoutUpdateStarted) {
          qDebug() << "Element updateLayout not started";
          return;
      } else if (layoutUpdateScheduled&&!resolved) {
          qDebug() << "Element updateLayout skip";
          return;
      } else if (layoutUpdateScheduled&&resolved) {
          qDebug() << "Element updateLayout exec";
          disconnect(instance,SIGNAL(diffFree()),this,SLOT(updateLayout()));
          layoutUpdateScheduled=false;
          updateLayoutNow();
      } else if (!resolved) {
          qDebug() << "Element updateLayout scheduled";
          connect(instance,SIGNAL(diffFree()),this,SLOT(updateLayout()));
          layoutUpdateScheduled=true;
      } else {
          qDebug() << "Element updateLayout update";
          updateLayoutNow();
      }
}

/*---------------------------------------------------------------------------*/

void Element::startLayoutUpdate() {
    qDebug() << "Element startLayoutUpdate";
    layoutUpdateStarted=true;
    if (!getItem()->isVisible()) {
        getItem()->setVisible(true);
    }
}

/*---------------------------------------------------------------------------*/

void Element::updateLayoutNow() {
    qDebug() << "Element updateLayoutNow";
    int H=layout->getWidth();
    int W=layout->getHeight();
    int T=layout->getLayoutTop()-layout->getMarginTop();
    int LT=layout->getLastTop();
    int L=layout->getLayoutLeft()-layout->getMarginLeft();
    int LL=layout->getLastLeft();

    layout->deleteLater();
    layout=buildFlexTree();

    if (LL==-1&&LT==-1) {
        layout->setLastTop(T);
        layout->setLastLeft(L);
    } else {
        Q_ASSERT(LL!=-1);
        Q_ASSERT(LT!=-1);
        T=LT;
        L=LL;
    }

    layout->printTree();
    layout->buildTree();
    layout->calculateLayoutLtr(T,L,H,W);
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
