#ifndef TIMERMONITOR_H
#define TIMERMONITOR_H

#include <QTimer>
#include <QtDebug>
#include <QObject>
#include <QJSValue>

#include "base/monitor.h"

namespace Quite {
namespace Monitors {

/*****************************************************************************/

class TimerMonitor : public Base::Monitor{
  Q_OBJECT
  private:
    QTimer* timer;
    QJSValue handler;
    bool started = false;
    bool canceled = false;
    bool finished = false;
    bool singleshot = false;
    int msec = 0;
  public:
    TimerMonitor(
        QJSValue handler,
        int msec,
        bool singleshot = true
    );
    virtual ~TimerMonitor();
    virtual bool isStarted() const;
    virtual bool isCanceled() const;
    virtual bool isFinished() const;
    virtual void start(QThreadPool* pool, QObject* engine);
    void cancel();
  private slots:
    void tick();
};

/*****************************************************************************/

} // namespace Monitors
} // namespace Quite

#endif // TIMERMONITOR_H
