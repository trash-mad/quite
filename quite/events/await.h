#ifndef AWAIT_H
#define AWAIT_H

#include <QtDebug>
#include <QObject>
#include <QJSEngine>
#include <QThreadPool>
#include <QCoreApplication>

#include "base/event.h"
#include "base/monitor.h"

using namespace Quite::Base;

namespace Quite {
namespace Events {

/*****************************************************************************/

class Await : public Event {
  private:
    Monitor* monitor;
  public:
    Await(Monitor* monitor);
    virtual ~Await();
    Monitor* getMonitor() const;
    virtual EventResult process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // AWAIT_H
