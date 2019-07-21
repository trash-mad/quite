#include "emitter.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Emitter::Emitter(QJSValue func, QObject* engine)
  : QObject(nullptr) {
    qDebug() << "Emitter ctor";
    this->engine = engine;
    this->func = func;
}

/*---------------------------------------------------------------------------*/

Emitter::~Emitter() {
    qDebug() << "Emitter dtor";
}

/*---------------------------------------------------------------------------*/

bool Emitter::isRequired() const {
    return required;
}

/*---------------------------------------------------------------------------*/

QJSValue Emitter::getFunc() const {
    return func;
}

/*---------------------------------------------------------------------------*/

QJSValueList Emitter::getArgs() const {
    return args;
}

/*---------------------------------------------------------------------------*/

QJSValue Emitter::fromObject(
    QJSValue origin,
    QJSEngine* eval,
    QObject* engine
) {
    if(origin.isCallable()) {
        Emitter* instance = new Emitter(origin, engine);
        QJSValue managed = eval->newQObject(
            instance
        ).property("call");
        QQmlEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
        managed.prototype().setProperty("_emitterOrigin", origin);
        return managed;
    } else {
        return origin;
    }
}

/*---------------------------------------------------------------------------*/

void Emitter::call(QJSValueList args) {

    QStringList tmp;
    for(int i=0; i!= args.length(); i++){
        tmp << args.at(i).toString();
    }
    qDebug() << "Emitter call" << tmp;

    QCoreApplication::postEvent(engine, new Events::Eval(func,args));
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
