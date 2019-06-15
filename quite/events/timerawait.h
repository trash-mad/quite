#ifndef TIMERAWAIT_H
#define TIMERAWAIT_H

#include <QTimer>
#include <QtDebug>
#include <QObject>
#include <QCoreApplication>

#include "base/event.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

class TimerAwait : public Base::Event {
  private:
    QTimer* timer;
  public:
    TimerAwait(QTimer* timer);
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
