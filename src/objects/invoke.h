#ifndef INVOKE_H
#define INVOKE_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>

#include "src/events/eval.h"

using namespace Quite::Events;

namespace Quite {
namespace Objects {

/*****************************************************************************/

class Invoke : public QObject {
  Q_OBJECT
  private:
    QJSValue func;
    QJSValue instance;
    QJSValueList args;
  public:
    Invoke(QJSValue func, QJSValue instance);
    virtual ~Invoke();
    Eval* createEval(QList<QVariant> args);
    static bool tryCast(QVariant src, Invoke*& dst);
};

/*****************************************************************************/

} // namespace Objects
} // namespace Quite

#endif // INVOKE_H
