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
    QJSValue createElementRestWrapper=eval->evaluate(
        "(function (instance) {"\
        "   function flatten(arr) { "\
        "       return arr.reduce(function (flat, toFlatten) { "\
        "           return flat.concat(Array.isArray(toFlatten) ? flatten(toFlatten) : toFlatten);"\
        "       }, []);" \
        "   };"\
        "   instance.createElement=function(type,props,...child){" \
        "       return instance.createElementInternal(type,props,flatten(child));" \
        "   }; " \
        "   return instance;" \
        "})"
    );
    global.setProperty("Quite",createElementRestWrapper.call({current}));
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
