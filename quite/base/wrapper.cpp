#include "wrapper.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Wrapper::Wrapper(const QJSValue& original)
  : QObject(nullptr) {
    qDebug() << "Wrapper ctor";
    object = new QJSValue(original);
}

/*---------------------------------------------------------------------------*/

Wrapper::~Wrapper() {
    qDebug() << "Wrapper dtor";
    delete object;
}

/*---------------------------------------------------------------------------*/

QJSValue Wrapper::call(QJSValueList args) {
    qDebug() << "Wrapper call";
    return object->call(args);
}

/*---------------------------------------------------------------------------*/

Wrapper *Wrapper::wrapObject(QObject *engine, const QJSValue object) {
    if(Wrapper::engine == nullptr) {
        Wrapper::engine = engine;
    }
    return new Wrapper(object);
}

/*---------------------------------------------------------------------------*/

QJSValue Wrapper::fromQObject(
    QObject *engine,
    QObject *obj,
    QJSEngine *eval
) {
    QJSValue object = eval->newQObject(obj);
    QJSValue result = eval->newObject();
    QJSValueIterator it(object);
    while (it.hasNext()) {
        it.next();
        if(it.value().isCallable()){
            QJSValue wrapped = eval->newQObject(
                wrapObject(engine, it.value())
            );
            result.setProperty(it.name(), wrapped.property("call"));
        }
    }
    return result;
}

/*---------------------------------------------------------------------------*/

QObject* Wrapper::engine = nullptr;

/*****************************************************************************/

} // namespace Base
} // namespace Quite
