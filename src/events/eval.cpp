#include "eval.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

Eval::Eval(QJSValue func, QJSValueList args, QJSValue instance)
  : Event() {
    qDebug() << "Eval ctor";
    this->instance = instance;
    this->func = func;
    this->args = args;
}

/*---------------------------------------------------------------------------*/

Eval::~Eval() {
    qDebug() << "Eval dtor";
}

/*---------------------------------------------------------------------------*/

EventResult Eval::process(
    QObject *engine,
    QJSEngine *eval,
    QThreadPool *pool
) {
    (void)(eval);
    (void)(pool);

    QJSValue res;
    if (instance.isUndefined()) {
        res = func.call(args);
    } else {
        res = func.callWithInstance(instance, args);
    }

    if(res.isError()){
        QCoreApplication::postEvent(engine, new ThrowError(res.toString()));
    }

    return EventResult::Ok;
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
