#ifndef AWAIT_H
#define AWAIT_H

#include <QtDebug>
#include <QObject>
#include <QJSEngine>
#include <QThreadPool>
#include <QCoreApplication>

#include "base/event.h"
#include "base/monitor.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

class Await : public Base::Event {
  private:
    Base::Monitor* monitor;
  public:
    Await(Base::Monitor* monitor);
    virtual ~Await();
    virtual void process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // AWAIT_H
