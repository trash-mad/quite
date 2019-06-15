#include "timerawait.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

TimerAwait::TimerAwait(QTimer *timer)
  : Base::Event() {
    //qDebug() << "TimerAwait ctor";
    this->timer = timer;
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
    if(timer->isActive()) {
        QCoreApplication::postEvent(engine, new TimerAwait(timer));
    } else {
        delete timer;
    }
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
