#ifndef BINDMONITOR_H
#define BINDMONITOR_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QReadWriteLock>

#include "src/base/monitor.h"
#include "src/objects/binder.h"

using namespace Quite::Base;
using namespace Quite::Objects;

namespace Quite {
namespace Monitors {

/*****************************************************************************/

class BindMonitor : public Monitor {
  private:
    QJSValue func;
    QJSValue result;
    QJSValue instance;
    bool started = false;
    bool finished = false;
    QReadWriteLock locker;
  public:
    BindMonitor(QJSValue func, QJSValue instance);
    virtual ~BindMonitor();
    virtual bool isStarted();
    virtual bool isCanceled();
    virtual bool isFinished();
    QJSValue getResult();
    virtual void start(QThreadPool* pool, QJSEngine* eval, QObject* engine);
};

/*****************************************************************************/

} // namespace Monitors
} // namespace Quite

#endif // BINDMONITOR_H
