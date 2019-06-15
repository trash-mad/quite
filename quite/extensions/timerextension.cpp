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

    QTimer* timer = new QTimer();
    timer->setSingleShot(true);
    timer->setInterval(1);

    Objects::TimerMonitor *monitor = new Objects::TimerMonitor(
        this,
        timer,
        handler,
        777
    );

    timer->start();

    QCoreApplication::sendEvent(parent(), new Events::TimerAwait(monitor));

    return QJSValue();
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
