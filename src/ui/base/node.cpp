#include "node.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

NodeType Node::getNodeType(QString type) {
    if (type == "Element") {
        return NodeType::ElementType;
    } else if(type == "Rectangle") {
        return NodeType::RectangleType;
    } else if(type == "Button") {
        return NodeType::ButtonType;
    } else if (type == "Window") {
        return NodeType::WindowType;
     } else {
        qCritical() << "getNodeType invalid node type" << type;
        return NodeType::NeverType;
    }
}

/*---------------------------------------------------------------------------*/

QMap<QString, QJSValue> Node::getNodeParams(QJSValue props) {
    QMap<QString, QJSValue> tmp;
    if(props.isNull()){
        return tmp;
    } else if(!props.isObject() ){
        qCritical() << "getNodeParams props is not object";
    } else {
        QJSValueIterator it(props);
        while (it.hasNext()) {
            it.next();
            tmp.insert(it.name(),it.value());
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
        qCritical() << "Node name not string not func";
    } else if(!props.isNull() && !props.isObject()) {
        qCritical() << "Node props is not object";
    } else if(!child.isUndefined() && !child.isArray()) {
        qCritical() << "Child is not array";
    } else {
        this->props = getNodeParams(props);
        this->child = castNodeList(child);
        this->type = getNodeType(type.toString());
    }
}

/*---------------------------------------------------------------------------*/

Node::~Node() {
    qDebug() << "Node dtor";
}

/*---------------------------------------------------------------------------*/

NodeType Node::getType() const {
    return type;
}

/*---------------------------------------------------------------------------*/

QLinkedList<Node *> Node::getChild() const {
    return child;
}

/*---------------------------------------------------------------------------*/

QMap<QString, QJSValue> Node::getProps() const {
    return props;
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

/*---------------------------------------------------------------------------*/

QJSValue Node::commitProps(QJSValue props) {
    qDebug() << "Node commitProps";
    this->props = getNodeParams(props);
    emit propsChanged(this->props);
    return QJSValue();
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
