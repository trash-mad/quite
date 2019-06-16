#include "monitor.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Monitor::Monitor()
  : QObject(nullptr) {
    qDebug() << "Monitor ctor";
}

/*---------------------------------------------------------------------------*/

Monitor::~Monitor() {
    qDebug() << "Monitor dtor";
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
