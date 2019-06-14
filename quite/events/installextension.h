#ifndef INSTALLEXTENSION_H
#define INSTALLEXTENSION_H

#include <QThreadPool>
#include <QJSEngine>
#include <QtDebug>
#include <QObject>
#include <QEvent>

#include "base/event.h"
#include "base/wrapper.h"
#include "base/extension.h"

#include "extensions/timerextension.h"

namespace Quite {

/*****************************************************************************/

enum Extension {
    TimerExtension
};

/*****************************************************************************/

namespace Events {

/*****************************************************************************/

class InstallExtension : public Base::Event {
  private:
    Quite::Extension extension;
  public:
    explicit InstallExtension(Quite::Extension extension);
    virtual ~InstallExtension();
    virtual void process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // INSTALLEXTENSION_H
