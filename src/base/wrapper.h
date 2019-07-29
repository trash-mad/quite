#ifndef WRAPPER_H
#define WRAPPER_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QQmlEngine>
#include <QJSValueIterator>
#include <QCoreApplication>

#include "src/base/emitter.h"
#include "src/events/eval.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

class Wrapper : public QObject {
  Q_OBJECT
  private:
    QObject* origin;
    QString property;
    QObject* engine;
    QJSEngine* eval;
  private:
    void check(bool found);
    void execEmit(Emitter* e);
  public:
    Wrapper(
        QObject* origin,
        QString property,
        QJSEngine* eval,
        QObject* engine
    );
    virtual ~Wrapper();
  public slots:
    QJSValue call(
        QJSValue p1=QJSValue(),
        QJSValue p2=QJSValue(),
        QJSValue p3=QJSValue(),
        QJSValue p4=QJSValue(),
        QJSValue p5=QJSValue(),
        QJSValue p6=QJSValue(),
        QJSValue p7=QJSValue(),
        QJSValue p8=QJSValue(),
        QJSValue p9=QJSValue(),
        QJSValue p10=QJSValue()
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
