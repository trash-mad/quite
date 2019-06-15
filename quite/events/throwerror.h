#ifndef THROWERROR_H
#define THROWERROR_H

#include <QtDebug>
#include <QObject>
#include <QString>
#include <QJSEngine>

#include "base/event.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

class ThrowError : public Base::Event {
  private:
    QString message;
  public:
    explicit ThrowError(QString message="");
    virtual ~ThrowError();
    virtual void process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // THROWERROR_H
