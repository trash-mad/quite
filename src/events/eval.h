#ifndef EVAL_H
#define EVAL_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QCoreApplication>

#include "src/base/event.h"
#include "src/events/throwerror.h"

using namespace Quite::Base;

namespace Quite {
namespace Events {

/*****************************************************************************/

class Eval : public Base::Event{
  private:
    QJSValue func;
    QJSValueList args;
  public:
    explicit Eval(QJSValue func, QJSValueList args);
    virtual ~Eval();
    virtual EventResult process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // EVAL_H
