#include "application.h"

namespace Quite {

/*****************************************************************************/

Application::Application()
  : QObject(nullptr) {
    qDebug() << "Application ctor" << QDateTime::currentDateTime().toTime_t();
    connect(&engine, SIGNAL(renderUi(Node*)), &manager, SLOT(renderUi(Node*)));
    connect(&manager, SIGNAL(closed()), &engine, SLOT(windowClosed()));
    connect(
        &manager,
        SIGNAL(eval(QJSValue,QJSValueList)),
        &engine,
        SLOT(evalFunc(QJSValue,QJSValueList))
    );
    connect(&engine, SIGNAL(done()), qApp, SLOT(quit()));
    engine.start();
}

/*---------------------------------------------------------------------------*/

Application::~Application() {
    qDebug() << "Application dtor";
}

/*---------------------------------------------------------------------------*/

void Application::logHandler(
    QtMsgType type,
    const QMessageLogContext &context,
    const QString &msg) {
    (void)(context);
    if(type == QtMsgType::QtInfoMsg) {
        std::cout << msg.toStdString() << "\n";
    } else if(type == QtMsgType::QtCriticalMsg) {
        std::cout << msg.toStdString() << "\n";
        abort();
    } else {
        QFile f(QDir::current().filePath("debug.txt"));
        if (f.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream(&f) << msg << "\n";
        } else {
            std::cout << "Can't append to debug.txt";
            abort();
        }
    }
}

/*---------------------------------------------------------------------------*/

int Application::exec(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    qInstallMessageHandler(logHandler);
    qRegisterMetaType<QJSValueList>("QJSValueList");
    Application a;
    a.installExtension(Extension::TimerExtension);
    a.installExtension(Extension::QuiteExtension);
    a.installExtension(Extension::ConsoleExtension);
    a.importModule("main.js");
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
