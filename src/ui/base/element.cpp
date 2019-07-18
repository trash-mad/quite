#include "element.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Element::Element(Node *node, QQmlEngine *engine, Element *parent)
  : QObject(parent) {
    qDebug() << "Element ctor";
    this->props = node->getProps();
    this->engine = engine;
    this->node = node;
}

/*---------------------------------------------------------------------------*/

Element::~Element() {
    qDebug() << "Element dtor";
    //node->deleteLater();
    delete item;
}

/*---------------------------------------------------------------------------*/

QLinkedList<Element*> Element::getChild() const {
    return child;
}

/*---------------------------------------------------------------------------*/

QMap<QString, QJSValue> Element::getProps() const {
    return props;
}

/*---------------------------------------------------------------------------*/

QQuickItem *Element::getItem() const {
    return item;
}

/*---------------------------------------------------------------------------*/

Node *Element::getNode() const {
    return node;
}

/*---------------------------------------------------------------------------*/

void Element::invoke(
    QString type,
    QVariant p1,
    QVariant p2,
    QVariant p3,
    QVariant p4
) {
    (void)(type);
    (void)(p1);
    (void)(p2);
    (void)(p3);
    (void)(p4);
    qDebug() << "Element default invoke";
}

/*---------------------------------------------------------------------------*/

void Element::updateProps(QMap<QString, QJSValue> props) {
    qDebug() << "Element updateProps";
    this->props = props;
    propsChanged();
}

/*---------------------------------------------------------------------------*/

void Element::updateProp(QString key, QJSValue value) {
    qDebug() << "Element updateProp" << key;
    props.insert(key, value);
}

/*---------------------------------------------------------------------------*/

void Element::receiveSubtree(QLinkedList<Element *> child) {
    qDebug() << "Element receiveSubtree";
    this->child = child;
    childChanged();
}

/*---------------------------------------------------------------------------*/

void Element::propsChanged() {
    qDebug() << "Element default propsChanged";
    QMap<QString, QJSValue>::iterator i;
    for(i = props.begin(); i!= props.end(); i++) {
        QString name = i.key();
        QVariant value = i.value().toVariant();
        item->setProperty(name.toStdString().c_str(),value);
    }
}

/*---------------------------------------------------------------------------*/

void Element::childChanged() {
    qDebug() << "Element default childChanged";
    QLinkedList<Element*>::iterator i;
    for (i=child.begin(); i!=child.end();i++) {
        Element* element = (*i);
        element->getItem()->setParentItem(item);
    }
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
