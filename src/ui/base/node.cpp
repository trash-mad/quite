#include "node.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

NodeType Node::getNodeType(QString type) {
    if (type == "Window") {
       return NodeType::Window;
    } else if(type == "Rectangle") {
        return NodeType::Rectangle;
    } else {
        qCritical() << "getNodeType invalid node type" << type;
        return NodeType::Never;
    }
}

/*---------------------------------------------------------------------------*/

QMap<QString, QVariant> Node::getNodeProps(QJSValue props) {
    QMap<QString, QVariant> tmp;
    if(props.isNull()){
            return tmp;
    } else if(!props.isObject() ){
        qCritical() << "getNodeProps props is not object";
    } else {
        QJSValueIterator it(props);
        while (it.hasNext()) {
            it.next();
            tmp.insert(it.name(),it.value().toVariant());
        }
    }
    return tmp;
}

/*---------------------------------------------------------------------------*/

bool Node::tryCastNode(QJSValue src, Node *&dst) {
    if(!src.isQObject()) {
        return false;
    } else {
        dst = qobject_cast<Node*>(src.toQObject());
        return dst!=nullptr;
    }
}

/*---------------------------------------------------------------------------*/

QLinkedList<Node *> Node::castNodeList(QJSValue arr) {
    QLinkedList<Node*> child;
    if(arr.isUndefined()) {
        return child;
    } if(!arr.isArray()) {
        qCritical() << "castNodeList arr is not array";
    } else {
        const int length = arr.property("length").toInt();
        for (int i = 0; i != length; i++) {
            Node* node = nullptr;
            QJSValue item = arr.property(i);
            if (!item.isQObject()) {
                qCritical() << "castNodeList arr is not array of qobject";
            } else if(!tryCastNode(item, node)) {
                qCritical() << "castNodeList arr is not array of Node";
            } else {
                child.append(node);
            }
        }
    }
    return child;
}

/*---------------------------------------------------------------------------*/

Node::Node(QJSValue type, QJSValue props, QJSValue child)
  : QObject(nullptr) {
    qDebug() << "Node ctor";
    if (!type.isString()) {
        qCritical() << "Node name is not string";
    } else if(!props.isNull() && !props.isObject()) {
        qCritical() << "Node props is not object";
    } else if(!child.isUndefined() && !child.isArray()) {
        qCritical() << "Child is not array";
    } else {
        this->type = getNodeType(type.toString());
        this->props = getNodeProps(props);
        this->child = castNodeList(child);
    }
}

/*---------------------------------------------------------------------------*/

Node::~Node() {
    qDebug() << "Node dtor";
}

/*---------------------------------------------------------------------------*/

QLinkedList<Node *> Node::getChild() const {
    return child;
}

/*---------------------------------------------------------------------------*/

QMap<QString, QVariant> Node::getProps() const {
    return props;
}

/*---------------------------------------------------------------------------*/

QJSValue Node::commitProps(QJSValue props) {
    qDebug() << "Node" << type << "commitProps";
    this->props = getNodeProps(props);
    emit propsChanged(this->props);
    return QJSValue();
}

/*---------------------------------------------------------------------------*/

QJSValue Node::commitChild(QJSValue child) {
    qDebug() << "Node" << type << "commitChild";
    QLinkedList<Node*>::iterator i;
    for (i = this->child.begin(); i != this->child.end(); i++){
        Node* node = (*i);
        node->deleteLater();
    }
    this->child = castNodeList(child);
    emit childChanged(this->child);
    return QJSValue();
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
