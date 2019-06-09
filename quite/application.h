#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include <QGuiApplication>
#include <QObject>

#include "base/engine.h"

using namespace Quite::Base;

namespace Quite {

/*****************************************************************************/

class Application : public QObject {
  Q_OBJECT
  private:
    Engine engine;
  protected:
    explicit Application();
    virtual ~Application();
  public:
    static int exec(int argc, char *argv[]);
};

/*****************************************************************************/

}

#endif // APPLICATION_H
