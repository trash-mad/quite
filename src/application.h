#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include <QGuiApplication>
#include <QDateTime>
#include <QObject>
#include <QDebug>
#include <QDir>

#include <iostream>

#include "src/base/engine.h"
#include "src/ui/base/node.h"
#include "src/ui/windowmanager.h"
#include "src/events/importmodule.h"
#include "src/events/installextension.h"

using namespace Quite::Ui::Base;
using namespace Quite::Events;
using namespace Quite::Ui;

namespace Quite {

/*****************************************************************************/

class Application : public QObject {
  Q_OBJECT
  private:
    Engine engine;
    WindowManager manager;
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