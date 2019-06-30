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
    generator.seed(QRandomGenerator::global()->bounded(256));
}

/*---------------------------------------------------------------------------*/

TimerExtension::~TimerExtension() {
    qDebug() << "TimerExtension dtor";
}

/*---------------------------------------------------------------------------*/

void TimerExtension::install(
    QJSValue global,
    QJSValue current,
    QJSEngine* eval
) {
    (void)(eval);
    qDebug() << "TimerExtension install";
    global.setProperty("setTimeout",current.property("setTimeout"));
    global.setProperty("clearTimeout",current.property("clearTimeout"));
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
        int id = -1;
        Monitors::TimerMonitor* monitor = new Monitors::TimerMonitor(
            handler,
            timeout.toInt()
        );
        id = append(monitor);
        monitor->setId(id);
        result = QJSValue(id);
        connect(monitor,SIGNAL(clear(int)),this,SLOT(clearPointer(int)));
        QCoreApplication::postEvent(parent(), new Events::Await(monitor));
    }

    return result;
}

/*---------------------------------------------------------------------------*/

QJSValue TimerExtension::clearTimeout(QJSValue timeout) {
    QJSValue result;
    if(timeout.isNumber()) {
        int id = timeout.toNumber();
        if(timers.contains(id)) {
            qDebug() << "TimerExtension clearTimeout" << id;
            timers.take(id)->cancel();
        } else {
            QCoreApplication::postEvent(
                parent(),
                new Events::ThrowError("clearTimeout id not exist")
            );
        }
    } else {
        QCoreApplication::postEvent(
            parent(),
            new Events::ThrowError("clearTimeout invalid id")
        );
    }
    return result;
}

/*---------------------------------------------------------------------------*/

void TimerExtension::clearPointer(int id) {
    qDebug() << "TimerExtension cleanup" << id;
    timers.remove(id);
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
