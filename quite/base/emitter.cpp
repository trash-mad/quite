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

QJSValue Emitter::fromObject(QJSValue origin, Emitter*& emitter, QJSEngine* eval) {
    if(origin.isCallable()) {
        emitter = new Emitter(origin);
        QJSValue managed = eval->newQObject(emitter);
        return managed.property("call");
    } else {
        return origin;
    }
}

/*---------------------------------------------------------------------------*/

void Emitter::call(QJSValueList args) {
    qDebug() << "Emitter call";
    this->args = args;
    required = true;
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
