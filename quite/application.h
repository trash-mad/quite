#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include <QGuiApplication>
#include <QObject>

#include <iostream>

#include "base/engine.h"
#include "events/importmodule.h"
#include "events/installextension.h"

using namespace Quite::Events;

namespace Quite {

/*****************************************************************************/

class Application : public QObject {
  Q_OBJECT
  private:
    Base::Engine engine;
  protected:
    explicit Application();
    virtual ~Application();
  public:
    static int exec(int argc, char *argv[]);
    void installExtension(Quite::Extension ext);
    void importModule(QString path);
};

/*****************************************************************************/

}

#endif // APPLICATION_H
