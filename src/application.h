#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCommandLineParser>
#include <QApplication>
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
#include "src/ui/base/dialog.h"
#include "src/objects/invoke.h"
#include "src/ui/base/element.h"
#include "src/objects/nodestruct.h"
#include "src/events/importmodule.h"
#include "src/events/installextension.h"

#include "src/ui/qml_providers/consoleprovider.h"
#include "src/ui/qml_components/windowcomponent.h"

#define QMLC QMessageLogContext

using namespace Quite::Ui::QmlComponents;
using namespace Quite::Ui::QmlProviders;

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
    static QtMessageHandler createLogHandler(
        bool verbose,
        QDir dir=QDir::current()
    );
  public:
    static int exec(int argc, char *argv[]);
    void installExtension(Quite::Extension ext);
    void importModule(QString path);
};

/*****************************************************************************/

}

#endif // APPLICATION_H
