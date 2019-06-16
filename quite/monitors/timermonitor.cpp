#include "timermonitor.h"

namespace Quite {
namespace Monitors {

/*****************************************************************************/

TimerMonitor::TimerMonitor(QJSValue handler, int msec, bool singleshot)
  : Base::Monitor() {
    qDebug() << "TimerMonitor ctor";
    this->handler = handler;
    this->singleshot = singleshot;
    this->msec = msec;
}

/*---------------------------------------------------------------------------*/

TimerMonitor::~TimerMonitor() {
    qDebug() << "TimerMonitor dtor";
    delete timer;
}

/*---------------------------------------------------------------------------*/

bool TimerMonitor::isStarted() const {
    return started;
}

/*---------------------------------------------------------------------------*/

bool TimerMonitor::isCanceled() const {
    return canceled;
}

/*---------------------------------------------------------------------------*/

bool TimerMonitor::isFinished() const {
    return finished;
}

/*---------------------------------------------------------------------------*/

void TimerMonitor::start(QThreadPool *pool, QObject *engine) {
    (void)(pool);
    (void)(engine);
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    started = true;
    timer->start(msec);
}

/*---------------------------------------------------------------------------*/

void TimerMonitor::cancel() {
    canceled = true;
    timer->stop();
}

/*---------------------------------------------------------------------------*/

void TimerMonitor::tick() {
    handler.call();
    if(singleshot) {
        finished = true;
    } else {
        timer->start(msec);
    }
}

/*****************************************************************************/

} // namespace Monitors
} // namespace Quite
