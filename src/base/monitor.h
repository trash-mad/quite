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

    virtual bool isStarted() const = 0;
    virtual bool isCanceled() const = 0;
    virtual bool isFinished() const = 0;

    virtual void start(QThreadPool* pool, QObject* engine) = 0;
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // MONITOR_H
