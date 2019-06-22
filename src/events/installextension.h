#ifndef INSTALLEXTENSION_H
#define INSTALLEXTENSION_H

#include <QThreadPool>
#include <QJSEngine>
#include <QtDebug>
#include <QObject>
#include <QEvent>

#include "src/base/event.h"
#include "src/base/wrapper.h"
#include "src/base/factory.h"
#include "src/base/extension.h"

#include "src/extensions/timerextension.h"
#include "src/extensions/quiteextension.h"
#include "src/extensions/consoleextension.h"

using namespace Quite::Base;

namespace Quite {

/*****************************************************************************/

enum Extension {
    TimerExtension,
    QuiteExtension,
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
