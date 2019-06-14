#include "application.h"

namespace Quite {

/*****************************************************************************/

Application::Application()
  : QObject(nullptr) {
    qDebug() << "Application ctor";
    connect(&engine, SIGNAL(done()), qApp, SLOT(quit()));
    engine.start();
}

/*---------------------------------------------------------------------------*/

Application::~Application() {
    qDebug() << "Application dtor";
}

/*---------------------------------------------------------------------------*/

int Application::exec(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    Application a;
    a.installExtension(Extension::TimerExtension);
    return app.exec();
}

/*---------------------------------------------------------------------------*/

void Application::installExtension(Extension ext) {
    QCoreApplication::postEvent(&engine, new InstallExtension(ext));
}

/*****************************************************************************/

} // namespace Quite
