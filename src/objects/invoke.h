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
    QList<QVariant> args;
  public:
    explicit Invoke(QJSValue func=QJSValue(), QJSValue instance=QJSValue());
    virtual ~Invoke();
    Eval* createEval();
    void addArgs(QList<QVariant> args);
    static bool tryCast(QVariant src, Invoke*& dst);
};

/*****************************************************************************/

} // namespace Objects
} // namespace Quite

#endif // INVOKE_H
