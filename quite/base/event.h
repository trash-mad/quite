#ifndef EVENT_H
#define EVENT_H

#include <QThreadPool>
#include <QJSEngine>
#include <QtDebug>
#include <QObject>
#include <QEvent>

namespace Quite {
namespace Base {

/*****************************************************************************/

class Event : public QEvent {
  public:
    explicit Event();
    virtual ~Event();
    virtual void process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    ) = 0;
    static QEvent::Type staticType();
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // EVENT_H
