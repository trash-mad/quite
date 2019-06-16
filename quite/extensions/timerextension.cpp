#include "timerextension.h"

namespace Quite {
namespace Extensions {

/*****************************************************************************/

TimerExtension::TimerExtension(QObject *parent)
  : Extension(parent) {
    qDebug() << "TimerExtension ctor";
}

/*---------------------------------------------------------------------------*/

TimerExtension::~TimerExtension() {
    qDebug() << "TimerExtension dtor";
}

/*---------------------------------------------------------------------------*/

void TimerExtension::install(QJSValue global, QJSValue current) {
    qDebug() << "TimerExtension install";
    global.setProperty("setTimeout",current.property("setTimeout"));
}

/*---------------------------------------------------------------------------*/

QJSValue TimerExtension::setTimeout(QJSValue handler, QJSValue timeout) {

    if(!handler.isCallable()) {
        qDebug() << "TimerExtension invalid handler";
        QCoreApplication::sendEvent(parent(), new Events::ThrowError(
            "setTimeout: invalid handler parameter"
        ));
    } else if (!timeout.isNumber()) {
        qDebug() << "TimerExtension invalid timeout";
        QCoreApplication::sendEvent(parent(), new Events::ThrowError(
            "setTimeout: invalid timeout"
        ));
    } else {
        Monitors::TimerMonitor* monitor = new Monitors::TimerMonitor(
            handler,
            timeout.toInt()
        );
        QCoreApplication::postEvent(parent(), new Events::Await(monitor));
    }

    return QJSValue();
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
