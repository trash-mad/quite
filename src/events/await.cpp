#include "await.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

Await::Await(Base::Monitor* monitor)
  : Base::Event() {
    qDebug() << "Await ctor";
    this->monitor = monitor;
}

/*---------------------------------------------------------------------------*/

Await::~Await() {
    qDebug() << "Await dtor";
}

/*---------------------------------------------------------------------------*/

Monitor *Await::getMonitor() const {
    return monitor;
}

/*---------------------------------------------------------------------------*/

EventResult Await::process(
    QObject *engine,
    QJSEngine* eval,
    QThreadPool *pool
) {
    if(monitor->isCanceled() || monitor->isFinished()) {
        qDebug() << "Awaiter monitor cleanup";
        delete monitor;
        return EventResult::Ok;
    } else {
        if(!monitor->isStarted()){
            qDebug() << "Awaiter monitor init";
            monitor->start(pool, eval, engine);
        }
        qDebug() << "Awaiter monitor skip";
        return EventResult::AwaiterRethrow;
    }
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
