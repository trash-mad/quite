#include "timermonitor.h"

namespace Quite {
namespace Objects {

/*****************************************************************************/

TimerMonitor::TimerMonitor(
    QObject* parent,
    QTimer* timer,
    QJSValue func,
    qint32 id)
  : QObject(parent) {
    qDebug() << "TimerMonitor ctor";
    this->timer = timer;
    this->func = func;
    this->id = id;
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
}

/*---------------------------------------------------------------------------*/

TimerMonitor::~TimerMonitor() {
    qDebug() << "TimerMonitor dtor";
    delete timer;
}

/*---------------------------------------------------------------------------*/

bool TimerMonitor::isActive() const {
    return timer->isActive();
}

/*---------------------------------------------------------------------------*/

void TimerMonitor::timeout() {
    qDebug() << "TimerMonitor call";
    func.call();
    emit done(id);
}

/*****************************************************************************/

} // namespace Objects
} // namespace Quite
