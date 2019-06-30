#include "bindmonitor.h"

namespace Quite {
namespace Monitors {

/*****************************************************************************/

BindMonitor::BindMonitor(QJSValue func, QJSValue instance)
  : Monitor() {
    qDebug() << "BindMonitor ctor";
    this->instance=instance;
    this->func=func;
}

/*---------------------------------------------------------------------------*/

BindMonitor::~BindMonitor() {
    qDebug() << "BindMonitor dtor";
}

/*---------------------------------------------------------------------------*/

bool BindMonitor::isStarted() {
    locker.lockForRead();
    bool started = this->started;
    locker.unlock();
    return started;
}

/*---------------------------------------------------------------------------*/

bool BindMonitor::isCanceled() {
    return false;
}

/*---------------------------------------------------------------------------*/

bool BindMonitor::isFinished() {
    locker.lockForRead();
    bool finished = this->finished;
    locker.unlock();
    return finished;
}

/*---------------------------------------------------------------------------*/

QJSValue BindMonitor::getResult() {
    locker.lockForWrite();
    QJSValue result = this->result;
    finished = true;
    locker.unlock();
    return result;
}

/*---------------------------------------------------------------------------*/

void BindMonitor::start(
    QThreadPool* pool,
    QJSEngine* eval,
    QObject* engine
) {
    qDebug() << "BindMonitor start";
    (void)(engine);
    (void)(pool);
    result = Binder::bind(func, instance, eval);
    locker.lockForWrite();
    started = true;
    locker.unlock();
}

/*****************************************************************************/

} // namespace Monitors
} // namespace Quite
