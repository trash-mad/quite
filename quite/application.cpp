#include "application.h"

namespace Quite {

/*****************************************************************************/

Application::Application()
  : QObject(nullptr) {
    qDebug() << "Application ctor";
    connect(&engine, SIGNAL(done()), qApp, SLOT(quit()));
    engine.start();
    QCoreApplication::postEvent(&engine, new Event());
}

/*---------------------------------------------------------------------------*/

Application::~Application() {
    qDebug() << "Application dtor";
}

/*---------------------------------------------------------------------------*/

int Application::exec(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    Application a;
    return app.exec();
}

/*****************************************************************************/

}
