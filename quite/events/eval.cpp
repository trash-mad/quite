#include "eval.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

Eval::Eval(QJSValue func, QJSValueList args)
  : Event() {
    qDebug() << "Eval ctor";
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
    QJSValue res = func.call(args);
    if(res.isError()){
        QCoreApplication::postEvent(engine, new ThrowError(res.toString()));
    }
    return EventResult::Ok;
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
