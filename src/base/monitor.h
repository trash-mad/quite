#ifndef MONITOR_H
#define MONITOR_H

#include <QtDebug>
#include <QObject>
#include <QJSEngine>
#include <QThreadPool>

namespace Quite {
namespace Base {

/*****************************************************************************/

class Monitor : public QObject {
  Q_OBJECT
  public:
    explicit Monitor();
    virtual ~Monitor();

    virtual bool isStarted() = 0;
    virtual bool isCanceled() = 0;
    virtual bool isFinished() = 0;

    virtual void start(
        QThreadPool* pool,
        QJSEngine* eval,
        QObject* engine
    ) = 0;
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // MONITOR_H
