#include "node.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Node::Node(QJSValue type, QJSValue props, QJSValue child)
  : QObject(nullptr) {
    qDebug() << "Node ctor";
    this->type=Node::castNodeType(type.toString());
    this->props=Node::castNodeParams(props);
    this->child=Node::castNodeList(child);
    {
        QLinkedList<Node*>::iterator iter;
        for (iter=this->child.begin();iter!=this->child.end();iter++) {
            Node* node = (*iter);
            totalChildCount+=node->getTotalChildCount();
            subscribeChildNode(node);
            //node->setParent(this);
        }
    }
    {
        QMap<QString,QJSValue>::iterator iter;
        for (iter=this->props.begin();iter!=this->props.end();iter++) {
            if (iter.key()=="key") {
                QJSValue key = iter.value();
                if (key.isNumber()) {
                    this->key=key.toInt();
                } else {
                    break;
                }
            } else {
                continue;
            }
        }
    }
}

/*---------------------------------------------------------------------------*/

Node::~Node() {
    qDebug() << "Node dtor";
}

/*---------------------------------------------------------------------------*/

void Node::subscribeChildNode(Node *node) {
    qDebug() << "Node subscribeChildNode";
    connect(
        node,
        SIGNAL(destroyed(QObject*)),
        this,
        SLOT(childDeletedHandler(QObject*))
    );
    connect(
        node,
        SIGNAL(incrementTotalChildCount()),
        this,
        SLOT(incrementTotalChildCountHandler())
    );
    connect(
        node,
        SIGNAL(decrementTotalChildCount()),
        this,
        SLOT(decrementTotalChildCountHandler())
    );
}

/*---------------------------------------------------------------------------*/

void Node::appendChild(Node *child) {
    qDebug() << "Node appendChild";
    this->child.append(child);
    subscribeChildNode(child);
    totalChildCount++;
    emit incrementTotalChildCount();
    emit childAppended(child);
}

/*---------------------------------------------------------------------------*/

void Node::insertAfterChild(Node *after, Node *child) {
    qDebug() << "Node insertChild";
    QLinkedList<Node*>::iterator iter;
    for (iter=this->child.begin();iter!=this->child.end();iter++) {
        Node* item = (*iter);
        if (after==item) {
            iter++;
            if (iter==this->child.end()) {
                this->child.append(child);
            } else {
                this->child.insert(iter,child);
            }
            subscribeChildNode(child);
            totalChildCount++;
            emit incrementTotalChildCount();
            emit childInsertedAfter(after, child);
            return;
        } else {
            continue;
        }
    }
    qCritical() << "Node insertChild before node not found";
}

/*---------------------------------------------------------------------------*/

void Node::childDeletedHandler(QObject *child) {
    qDebug() << "Node childDeletedHandler";
    QLinkedList<Node*>::iterator iter;
    for (iter=this->child.begin();iter!=this->child.end();iter++) {
        if (child==(*iter)) {
            this->child.erase(iter);
            totalChildCount--;
            emit decrementTotalChildCount();
            break;
        } else {
            continue;
        }
    }
}

/*---------------------------------------------------------------------------*/

void Node::mergeProps(Node *node) {
    qDebug() << "Node mergeProps";
    QMap<QString,QJSValue> nodeProps=node->getProps();
    bool update=false;
    if (nodeProps.count()!=props.count()) {
        update=true;
    } else {
        for (int i=0;i!=props.count();i++) {
            QString propKey=props.keys().at(i);
            QString nodeKey=nodeProps.keys().at(i);
            QJSValue propValue=props.values().at(i);
            QJSValue nodeValue=nodeProps.values().at(i);
            if (propKey!=nodeKey) {
                update=true;
                break;
            } else if (!propValue.equals(nodeValue)) {
                update=true;
                break;
            } else {
                continue;
            }
        }
    }
    /*
     *  GC merged node and commit props if need
     */
    QMetaObject::invokeMethod(
        node,
        "deleteLater",
        Qt::ConnectionType::QueuedConnection
    );
    //node->deleteLater();
    if (update) {
        this->props=nodeProps;
        commitProps();
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

/*
 * Метод изымает данные из QJSValue в QVariant на стороне
 * потока JavaScript и вещает в поток QML через сигнал
 * propsChanged()
 *
 * Должен быть вызван при построении древа компонентов в Manager и
 * при обновлении контекста выполнения instance
 */
void Node::commitProps() {
    qDebug() << "Node commitProps";
    QMap<QString, QVariant> tmp;
    QMap<QString, QJSValue>::iterator iter;
    for (iter=props.begin();iter!=props.end();iter++) {
        if (iter.key()=="key") {
            key=iter.value().toInt();
        } else if (iter.value().isCallable()) {
            tmp.insert(iter.key(),QVariant::fromValue(new Invoke(
               iter.value(),
               context
            )));
        } else {
            tmp.insert(iter.key(),iter.value().toVariant());
        }
    }
    emit propsChanged(tmp);
}

/*---------------------------------------------------------------------------*/

/*
 * Метод осуществляет привязку вызываемых функций к инстанции компонента,
 * вызывая commitProps и обновляя ссылку на актуальную инстанцию.
 *
 * Должен быть переопределен в ComponentNode, чтобы коллбеки из свойств
 * получили вышестоящий контекст, а дочерние компоненты выполнялись в текущем
 * контексте
 *
 * По умолчанию работает рекурсивно для всего древа.
 */
void Node::updateContext(QJSValue context,  bool recursive) {
    this->context=context;
    commitProps();
    if (recursive) {
        updateChildContext(context);
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void Node::updateChildContext(QJSValue context) {
    qDebug() << "Node updateChildContext";
    QLinkedList<Node*>::iterator iter;
    for (iter=this->child.begin();iter!=this->child.end();iter++) {
        (*iter)->updateContext(context);
    }
}

/*---------------------------------------------------------------------------*/

QMap<QString, QJSValue> Node::getProps() const {
    return props;
}

/*---------------------------------------------------------------------------*/

QLinkedList<Node *> Node::getChild() const {
    return child;
}

/*---------------------------------------------------------------------------*/

int Node::getTotalChildCount() const {
    return totalChildCount;
}

/*---------------------------------------------------------------------------*/

NodeType Node::getEnumType() const {
    return type;
}

/*---------------------------------------------------------------------------*/

int Node::getType() const {
    return static_cast<int>(type);
}

/*---------------------------------------------------------------------------*/

int Node::getKey() const {
    return key;
}

/*---------------------------------------------------------------------------*/

QMap<QString, QJSValue> Node::castNodeParams(QJSValue props) {
    QMap<QString, QJSValue> tmp;
    if(props.isNull()){
        return tmp;
    } else if(!props.isObject() ){
        qCritical() << "castNodeParams props is not object";
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

QLinkedList<Node *> Node::castNodeList(QJSValue arr) {
    QLinkedList<Node*> child;
    if(arr.isUndefined()) {
        return child;
    } if(!arr.isArray()) {
        qCritical() << "castNodeList arr is not array";
    } else {
        const uint length = arr.property("length").toUInt();
        for (uint i = 0; i != length; i++) {
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

bool Node::tryCastNode(QJSValue src, Node *&dst) {
    if(!src.isQObject()) {
        return false;
    } else {
        dst = qobject_cast<Node*>(src.toQObject());
        return dst!=nullptr;
    }
}

/*---------------------------------------------------------------------------*/

NodeType Node::castNodeType(QString type) {
    if(type == "Component") {
        return NodeType::ComponentType;
    } else if (type == "Fragment") {
        return NodeType::FragmentType;
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

void Node::incrementTotalChildCountHandler() {
    totalChildCount++;
    emit incrementTotalChildCount();
}

/*---------------------------------------------------------------------------*/

void Node::decrementTotalChildCountHandler() {
    totalChildCount--;
    emit decrementTotalChildCount();
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
