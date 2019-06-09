#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QtDebug>
#include <QEvent>

namespace Quite {
namespace Base {

/*****************************************************************************/

class Event : public QEvent {
  public:
    explicit Event();
    virtual ~Event();
    static QEvent::Type staticType();
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // EVENT_H
