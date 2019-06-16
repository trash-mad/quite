#include "timerextension.h"

namespace Quite {
namespace Extensions {

/*****************************************************************************/

int TimerExtension::append(Monitors::TimerMonitor* timer) {
    int id = -1;
    if(timers.count() == MAXIMUM_TIMERS){
        qCritical() << "Maximum timers count limit";
    } else {
        do {
            id = generator.bounded(MAXIMUM_TIMERS);
        } while (timers.contains(id));
    }
    timers.insert(id,timer);
    return id;
}

/*---------------------------------------------------------------------------*/

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
    QJSValue result;
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
        result = append(monitor);
        QCoreApplication::postEvent(parent(), new Events::Await(monitor));
    }

    return result;
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
