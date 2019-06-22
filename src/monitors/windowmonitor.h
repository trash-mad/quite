#ifndef WINDOWMONITOR_H
#define WINDOWMONITOR_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>

#include "src/base/monitor.h"
#include "src/ui/components/window.h"

using namespace Quite::Base;
using namespace Quite::Ui::Components;

namespace Quite {
namespace Monitors {

/*****************************************************************************/

class WindowMonitor : public Monitor {
  private:
    Window* window;
  public:
    WindowMonitor(Window* window);
    virtual ~WindowMonitor();
    virtual bool isStarted() const;
    virtual bool isCanceled() const;
    virtual bool isFinished() const;
    virtual void start(QThreadPool* pool, QObject* engine);
};

/*****************************************************************************/

} // namespace Monitors
} // namespace Quite

#endif // WINDOWMONITOR_H
