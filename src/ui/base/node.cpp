#include "node.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

NodeType Node::getNodeType(QString type) {
    if(type == "Rectangle") {
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

Node::Node(QObject* parent)
 :  QObject(parent) {
    qDebug() << "Node ctor";
}

/*---------------------------------------------------------------------------*/

Node::Node(QJSValue type, QJSValue props, QJSValue child)
  : Node() {
    qDebug() << "Node dtor";

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    this->type = getNodeType(type.toString());
    this->props = getNodeParams(props);
    this->child = castNodeList(child);

    QLinkedList<Node*>::iterator iter;
    for (iter=this->child.begin();iter!=this->child.end();iter++) {
        Node* item = (*iter);
        item->setParent(this);
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

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
