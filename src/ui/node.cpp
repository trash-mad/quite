#include "node.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

bool Node::tryCast(QJSValue src, Node *&dst) {
    if(!src.isQObject()) {
        return false;
    } else {
        dst = qobject_cast<Node*>(src.toQObject());
        if( dst == nullptr ) {
            return false;
        } else {
            return true;
        }
    }
}

/*---------------------------------------------------------------------------*/

Node::Node(QObject *parent, QQmlEngine *engine)
  : QObject(parent) {
    qDebug() << "Node ctor";
    this->engine = engine;
}

/*---------------------------------------------------------------------------*/

Node::~Node() {
    qDebug() << "Node dtor";
    QLinkedList<Node*>::iterator iter = children.begin();
    while (iter != children.end()) {
        Node* child = *iter;
        child->deleteLater();
        iter.operator++();
    }
}

/*void Node::appendChild(FiberNode *child) {
    qDebug() << "Node appendChild ";
    children.append(child);
    child->setParent(this);
    child->node->setParentItem(node);
}

void Node::removeChild(FiberNode *child) {
    qDebug() << "Node removeChild";
    children.removeOne(child);
    child->setParent(nullptr);
    child->node->setParentItem(nullptr);
}*/

/*---------------------------------------------------------------------------*/

QJSValue Node::appendChild(QJSValue child) {
    Node* node = nullptr;
    if(!tryCast(child, node)){
        qCritical() << "Node appendChild invalid child";
        qApp->exit(-1);
    } else {
        appendChild(node);
    }
    return QJSValue();
}

/*---------------------------------------------------------------------------*/

QJSValue Node::removeChild(QJSValue child) {
    Node* node = nullptr;
    if(!tryCast(child, node)){
        qCritical() << "Node removeChild invalid child";
        qApp->exit(-1);
    } else {
        removeChild(node);
    }
    return QJSValue();
}

/*---------------------------------------------------------------------------*/

QJSValue Node::insertBefore(QJSValue child, QJSValue beforeChild) {
    Node* node = nullptr;
    Node* beforeNode = nullptr;
    if(!tryCast(child, node)){
        qCritical() << "Node insertBefore invalid child";
        qApp->exit(-1);
    } else if(!tryCast(beforeChild, beforeNode)) {
        qCritical() << "Node insertBefore invalid before";
        qApp->exit(-1);
    } else {
        insertBefore(node, beforeNode);
    }
    return QJSValue();
}

/*---------------------------------------------------------------------------*/

QJSValue Node::commitUpdate(QJSValue props) {
    if( !props.isArray() ){
        qCritical() << "Node commitUpdate props is not array";
    } else {
        QVariant var = props.toVariant();
        QSequentialIterable iterable = var.value<QSequentialIterable>();
        QMap<QString, QVariant> tmp;
        for ( const QVariant &v : iterable ) {
            if(v.canConvert<QVariantMap>()) {
                QVariantMap map = qvariant_cast<QVariantMap>(v);
                QVariantMap::const_iterator iter;
                QString key = "";
                QVariant value = QVariant();
                for(iter = map.begin(); iter != map.end();++iter) {
                    if(iter.key() == "key") {
                        key = iter.value().toString();
                    } else if(iter.key() == "value") {
                        value = iter.value();
                    }
                }
                if(key.isEmpty()||value.isNull()){
                    qCritical() << "Node commitUpdate empty key or value";
                } else {
                    tmp.insert(key,value);
                }
            } else {
                qCritical() << "Node commitUpdate invalid list";
            }
        }
        commitUpdate(tmp);
    }
    return QJSValue();
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
