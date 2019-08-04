#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include <QGuiApplication>
#include <QDateTime>
#include <QObject>
#include <QVector>
#include <QDebug>
#include <QMutex>
#include <QDir>

#include <iostream>

#include "src/ui/manager.h"
#include "src/base/engine.h"
#include "src/ui/base/node.h"
#include "src/objects/invoke.h"
#include "src/ui/base/element.h"
#include "src/objects/nodestruct.h"
#include "src/events/importmodule.h"
#include "src/events/installextension.h"
#include "src/ui/components/windowcomponent.h"

using namespace Quite::Ui::Components;
using namespace Quite::Ui::Base;
using namespace Quite::Monitors;
using namespace Quite::Objects;
using namespace Quite::Events;
using namespace Quite::Ui;

namespace Quite {

/*****************************************************************************/

class Application : public QObject {
  Q_OBJECT
  private:
    Engine engine;
    Manager manager;
  protected:
    explicit Application();
    virtual ~Application();
  private:
    static void logHandler(
        QtMsgType type,
        const QMessageLogContext &context,
        const QString &msg
    );
  public:
    static int exec(int argc, char *argv[]);
    void installExtension(Quite::Extension ext);
    void importModule(QString path);
};

/*****************************************************************************/

}

#endif // APPLICATION_H
