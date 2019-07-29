#include "quiteextension.h"

namespace Quite {
namespace Extensions {

/*****************************************************************************/

QuiteExtension::QuiteExtension(QObject* parent)
  : Extension(parent) {
    qDebug() << "QuiteExtension ctor";
}

/*---------------------------------------------------------------------------*/

QuiteExtension::~QuiteExtension() {
    qDebug() << "QuiteExtension dtor";
}

/*---------------------------------------------------------------------------*/

void QuiteExtension::install(
    QJSValue global,
    QJSValue current,
    QJSEngine* eval
) {
    qDebug() << "QuiteExtension install";
    global.setProperty("Quite", current);
    this->eval = eval;
}

/*---------------------------------------------------------------------------*/

QJSValue QuiteExtension::render(QJSValue root) {
    qDebug() << "QuiteExtension render";
    Node* node = nullptr;
    if(!Node::tryCastNode(root,node)){
        QCoreApplication::sendEvent(parent(), new ThrowError(
            "render: invalid parameter rootNode"
        ));
    } else {
        QCoreApplication::postEvent(parent(), new RenderUi(node));
    }
    return QJSValue();
}

/*---------------------------------------------------------------------------*/

void QuiteExtension::parseChildElement(QJSValue child, QJSValueList& arr) {
    qDebug() << "QuiteExtension parseChildElement";
    Node* node=nullptr;
    if (child.isUndefined()) {
        return;
    } else if (child.isArray()) {
        const int length = child.property("length").toInt();
        for (int i=0;i!=length;i++) {
            arr.append(child.property(static_cast<uint>(i)));
        }
    } else {
        if (Node::tryCastNode(child,node)) {
            if (node->getType()==NodeType::FragmentType) {
                QLinkedList<Node*>::iterator iter;
                QLinkedList<Node*> nodes = node->getChild();
                for (iter=nodes.begin();iter!=nodes.end();iter++) {
                    arr.append(eval->newQObject(*iter));
                }
                return;
            } else {
                arr.append(child);
            }
        } else {
            qCritical() << "QuiteExtension parseChildElement invalid child";
        }
    }
}

/*---------------------------------------------------------------------------*/

QJSValue QuiteExtension::createElement(
    QJSValue type,
    QJSValue props,
    QJSValue child1,
    QJSValue child2,
    QJSValue child3,
    QJSValue child4,
    QJSValue child5,
    QJSValue child6,
    QJSValue child7,
    QJSValue child8
) {
    qDebug() << "QuiteExtension createElement";
    QJSValueList child;
    parseChildElement(child1, child);
    parseChildElement(child2, child);
    parseChildElement(child3, child);
    parseChildElement(child4, child);
    parseChildElement(child5, child);
    parseChildElement(child6, child);
    parseChildElement(child7, child);
    parseChildElement(child8, child);
    QJSValue arr = eval->newArray(static_cast<uint>(child.length()));
    QJSValueList::iterator iter;
    uint i=0;
    for (iter=child.begin();iter!=child.end();iter++) {
        arr.setProperty(i,*iter);
        i++;
    }
    return createElementInternal(type, props, arr);
}

/*---------------------------------------------------------------------------*/

QJSValue QuiteExtension::createElementInternal(
    QJSValue type,
    QJSValue props,
    QJSValue child
) {
    Node* node = nullptr;
    qDebug() << "QuiteExtension createElementInternal";
    if (type.isCallable()) {
        QJSValue origin = type.prototype().property("_emitterOrigin");
        QJSValue instance = origin.callAsConstructor({props});
        QJSValue render = instance.property("render");
        QJSValue state = instance.property("state");
        instance.setProperty("props", props);
        instance.setProperty("state", state);
        node = new ComponentNode(eval, instance, render);
    } else {
        node = new Node(type, props, child);
    }
    return eval->newQObject(node);
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
