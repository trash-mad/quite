#include "event.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Event::Event()
  : QEvent(Event::staticType()) {
    qDebug() << "Event ctor";
}

/*---------------------------------------------------------------------------*/

Event::~Event() {
    qDebug() << "Event dtor";
}

/*---------------------------------------------------------------------------*/

QEvent::Type Event::staticType() {
    static int type = QEvent::registerEventType();
    return static_cast<QEvent::Type>(type);
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
