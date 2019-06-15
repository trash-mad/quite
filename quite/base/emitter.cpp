#include "emitter.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Emitter::Emitter(QJSValue func)
  : QObject(nullptr) {
    qDebug() << "Emitter ctor";
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

QJSValue Emitter::fromObject(QJSValue origin, QJSEngine* eval) {
    if(origin.isCallable()) {
        QJSValue managed = eval->newQObject(new Emitter(origin));
        return managed.property("call");
    } else {
        return origin;
    }
}

/*---------------------------------------------------------------------------*/

void Emitter::call(QJSValueList args) {
    qDebug() << "Emitter call";
    QCoreApplication::postEvent(engine, new Events::Eval(func,args));
}

/*---------------------------------------------------------------------------*/

QObject* Emitter::engine = nullptr;

/*****************************************************************************/

} // namespace Base
} // namespace Quite
