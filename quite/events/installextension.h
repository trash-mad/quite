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
#include "extensions/consoleextension.h"

using namespace Quite::Base;

namespace Quite {

/*****************************************************************************/

enum Extension {
    TimerExtension,
    ConsoleExtension
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
    virtual EventResult process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // INSTALLEXTENSION_H
