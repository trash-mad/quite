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

void Await::process(QObject *engine, QJSEngine *eval, QThreadPool *pool) {
    (void)(eval);
    if(monitor->isCanceled() || monitor->isFinished()) {
        qDebug() << "Awaiter monitor cleanup";
        delete monitor;
    } else {
        if(!monitor->isStarted()){
            qDebug() << "Awaiter monitor init";
            monitor->start(pool, engine);
        }
        qDebug() << "Awaiter monitor skip";
        QCoreApplication::postEvent(
            engine,
            new Await(monitor),
            Qt::EventPriority::LowEventPriority
        );
    }
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
