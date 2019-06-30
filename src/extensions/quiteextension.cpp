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

QJSValue QuiteExtension::createElement(
    QJSValue type,
    QJSValue props,
    QJSValue child1,
    QJSValue child2,
    QJSValue child3
) {
    qDebug() << "QuiteExtension createElement";
    QJSValue child;
    if(child1.isUndefined()) {
        child = QJSValue();
    } else if(child2.isUndefined()) {
        child = eval->newArray(1);
        child.setProperty(0, child1);
    } else if(child3.isUndefined()) {
        child = eval->newArray(2);
        child.setProperty(0, child1);
        child.setProperty(1, child2);
    } else {
        child = eval->newArray(3);
        child.setProperty(0, child1);
        child.setProperty(1, child2);
        child.setProperty(2, child3);
    }
    return createElementInternal(type, props, child);
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
        node = new Element(eval, instance, props, state, render);
    } else {
        node = new Node(type, props, child);
    }

    return eval->newQObject(node);
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
