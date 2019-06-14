#ifndef TIMEREXTENSION_H
#define TIMEREXTENSION_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QJSValueIterator>

#include "base/extension.h"

using namespace Quite::Base;

namespace Quite {
namespace Extensions {

/*****************************************************************************/

class TimerExtension : public Extension {
  Q_OBJECT
  public:
    explicit TimerExtension(QObject* parent = nullptr);
    virtual ~TimerExtension();
    virtual void install(const QJSValue& global, const QJSValue& current);
  public slots:
    void setTimeout(QJSValue handler, QJSValue timeout);
};

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite

#endif // TIMEREXTENSION_H
