#include "throwerror.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

ThrowError::ThrowError(QString message)
  : Event() {
    qDebug() << "ThrowError ctor";
    this->message = message;
}

/*---------------------------------------------------------------------------*/

ThrowError::~ThrowError() {
    qDebug() << "ThrowError dtor";
}

/*---------------------------------------------------------------------------*/

EventResult ThrowError::process(
    QObject *engine,
    QJSEngine* eval,
    QThreadPool *pool
) {
    qCritical() << "ThrowError: " << message;
    (void)(engine);
    (void)(pool);
    eval->throwError(
        QString("RUNTIME_ERROR %1").arg(
            message
        )
    );
    return EventResult::Ok;
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
