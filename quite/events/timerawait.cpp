#include "timerawait.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

TimerAwait::TimerAwait(Objects::TimerMonitor *monitor)
  : Base::Event() {
    //qDebug() << "TimerAwait ctor";
    this->monitor = monitor;
}

/*---------------------------------------------------------------------------*/

TimerAwait::~TimerAwait() {
    //qDebug() << "TimerAwait dtor";
}

/*---------------------------------------------------------------------------*/

void TimerAwait::process(
    QObject *engine,
    QJSEngine *eval,
    QThreadPool *pool
) {
    //qDebug() << "TimerAwait process";
    if(monitor->isActive()) {
        QCoreApplication::postEvent(engine, new TimerAwait(monitor));
    } else {
        monitor->deleteLater();
    }
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
