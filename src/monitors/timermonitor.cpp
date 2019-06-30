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

void TimerMonitor::setId(int id) {
    this->id = id;
}

/*---------------------------------------------------------------------------*/

TimerMonitor::~TimerMonitor() {
    qDebug() << "TimerMonitor dtor";
    delete timer;
}

/*---------------------------------------------------------------------------*/

bool TimerMonitor::isStarted() {
    return started;
}

/*---------------------------------------------------------------------------*/

bool TimerMonitor::isCanceled() {
    return canceled;
}

/*---------------------------------------------------------------------------*/

bool TimerMonitor::isFinished() {
    return finished;
}

/*---------------------------------------------------------------------------*/

void TimerMonitor::start(
    QThreadPool *pool,
    QJSEngine* eval,
    QObject *engine
) {
    (void)(pool);
    (void)(eval);
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
    if(timer!=nullptr){
        timer->stop();
    }
}

/*---------------------------------------------------------------------------*/

void TimerMonitor::tick() {
    handler.call();
    if(singleshot) {
        finished = true;
        emit clear(id);
    } else {
        timer->start(msec);
    }
}

/*****************************************************************************/

} // namespace Monitors
} // namespace Quite
