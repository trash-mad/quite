#include "application.h"

namespace Quite {

/*****************************************************************************/

static void log(
    QtMsgType type,
    const QMessageLogContext &context,
    const QString &msg
){
    (void)(context);
    if(type == QtMsgType::QtDebugMsg){
        QFile outFile("/home/tripolskypetr/debug.txt");
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << msg << endl;
        outFile.close();
    } else {
        std::cout << msg.toStdString().c_str();
    }
}

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
    //qInstallMessageHandler(log);
    Application a;
    a.installExtension(Extension::TimerExtension);
    a.importModule("/home/tripolskypetr/test.js");
    return app.exec();
}

/*---------------------------------------------------------------------------*/

void Application::installExtension(Extension ext) {
    QCoreApplication::postEvent(&engine, new InstallExtension(ext));
}

/*---------------------------------------------------------------------------*/

void Application::importModule(QString path) {
    QCoreApplication::postEvent(&engine, new ImportModule(path));
}

/*****************************************************************************/

} // namespace Quite
