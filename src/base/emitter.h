#ifndef EMITTER_H
#define EMITTER_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QQmlEngine>
#include <QStringList>

#include "src/events/eval.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

class Emitter : public QObject {
  Q_OBJECT
  private:
    bool required = false;
    QJSValue func;
    QObject* engine;
    QJSValueList args;
  private:
    explicit Emitter(QJSValue func, QObject* engine);
    virtual ~Emitter();
  public slots:
    void call(QJSValueList args = QJSValueList());
  public:
    bool isRequired() const;
    QJSValue getFunc() const;
    QJSValueList getArgs() const;
    static QJSValue fromObject(
        QJSValue origin,
        QJSEngine* eval,
        QObject* engine
    );
    friend class Wrapper;
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // EMITTER_H
