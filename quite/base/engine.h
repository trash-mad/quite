#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QtDebug>
#include <QThread>
#include <QJSValue>
#include <QVariant>
#include <QJSEngine>
#include <QEventLoop>
#include <QThreadPool>
#include <QEventLoopLocker>
#include <QJSValueIterator>

#include "base/event.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

class Engine : public QThread {
  Q_OBJECT
  private:
    QThreadPool* pool;
    QJSEngine* eval;
  public:
    explicit Engine(QObject *parent = 0);
    virtual ~Engine();
  protected:
    virtual void run();
    virtual bool event(QEvent* event);
    virtual bool eventFilter(QObject *obj, QEvent *event);
  signals:
    void done();
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // ENGINE_H
