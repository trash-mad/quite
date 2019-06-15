#ifndef TIMER_H
#define TIMER_H

#include <QTime>
#include <QtDebug>
#include <QObject>
#include <QCoreApplication>

#include "base/event.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

class Timer : public Base::Event {
  private:
    Base::Event* execute = nullptr;
    bool canceled = false;
    bool interval = false;
    QTime expired;
  public:
    Timer(QTime expired, Base::Event* execute, bool interval = false);
    virtual ~Timer();
    virtual bool process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // TIMER_H
