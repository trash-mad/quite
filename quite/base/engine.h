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
#include <QJSValueIterator>

#include "base/event.h"
#include "base/wrapper.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

class Engine : public QThread {
  Q_OBJECT
  private:
    QThread* _initialThread;
    QThreadPool* _pool;
    QJSEngine* _eval;
  public:
    explicit Engine(QObject *parent = 0);
    virtual ~Engine();
    QJSValue fromQObject(QObject* object);
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
