#include "windowmonitor.h"

namespace Quite {
namespace Monitors {

/*****************************************************************************/

WindowMonitor::WindowMonitor(Window* window)
  : Monitor() {
    qDebug() << "WindowMonitor ctor";
    this->window = window;
}

/*---------------------------------------------------------------------------*/

WindowMonitor::~WindowMonitor() {
    qDebug() << "WindowMonitor dtor";
}

/*---------------------------------------------------------------------------*/

bool WindowMonitor::isStarted() const {
    return true;
}

/*---------------------------------------------------------------------------*/

bool WindowMonitor::isCanceled() const {
    return false;
}

/*---------------------------------------------------------------------------*/

bool WindowMonitor::isFinished() const {
    return window->isClosed();
}

/*---------------------------------------------------------------------------*/

void WindowMonitor::start(QThreadPool *pool, QObject *engine){
    (void)(pool);
    (void)(engine);
}

/*****************************************************************************/

} // namespace Monitors
} // namespace Quite
