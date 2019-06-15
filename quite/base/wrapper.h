#ifndef WRAPPER_H
#define WRAPPER_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QJSValueIterator>
#include <QCoreApplication>

#include "base/emitter.h"
#include "events/eval.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

class Wrapper : public QObject {
  Q_OBJECT
  private:
    static QJSEngine* eval;
    QObject* origin;
    QString property;
  private:
    void check(bool found);
    void execEmit(Emitter* e);
  public:
    Wrapper(QObject* origin, QString property);
    virtual ~Wrapper();
  public slots:
    QJSValue call(
        QJSValue p1=QJSValue(),
        QJSValue p2=QJSValue(),
        QJSValue p3=QJSValue(),
        QJSValue p4=QJSValue(),
        QJSValue p5=QJSValue()
    );

  public:
    static QJSValue fromQObject(
        QObject* engine,
        QObject* obj,
        QJSEngine* eval
    );
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // WRAPPER_H
