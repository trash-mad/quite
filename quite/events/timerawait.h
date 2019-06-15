#ifndef TIMERAWAIT_H
#define TIMERAWAIT_H

#include <QTimer>
#include <QtDebug>
#include <QObject>
#include <QCoreApplication>

#include "base/event.h"
#include "objects/timermonitor.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

class TimerAwait : public Base::Event {
  private:
    Objects::TimerMonitor *monitor;
  public:
    TimerAwait(Objects::TimerMonitor *monitor);
    virtual ~TimerAwait();
    virtual void process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // TIMERAWAIT_H
