#include "application.h"

namespace Quite {

/*****************************************************************************/

Application::Application()
  : QObject(nullptr) {
    qDebug() << "Application ctor" << QDateTime::currentDateTime().toTime_t();
    connect(&engine, SIGNAL(renderUi(Node*)), &manager, SLOT(renderUi(Node*)));
    connect(&manager, SIGNAL(closed()), &engine, SLOT(windowClosed()));
    connect(
        &engine,
        SIGNAL(renderDialog(IDialog*)),
        &manager,
        SLOT(renderDialog(IDialog*)),
        Qt::ConnectionType::QueuedConnection
    );
    connect(
        &manager,
        SIGNAL(invoke(Invoke*)),
        &engine,
        SLOT(invokeHandler(Invoke*))
    );
    connect(
        &manager,
        SIGNAL(closed()),
        &engine,
        SLOT(windowClosed())
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
    Q_UNUSED(context);
    static QMutex mutex;
    mutex.lock();
    if(type == QtMsgType::QtInfoMsg) {
        std::cout << msg.toStdString() << "\n";
    } else if(type == QtMsgType::QtCriticalMsg) {
        std::cout << msg.toStdString() << "\n";
        mutex.unlock();
        abort();
    } else {
        QFile f(QDir::current().filePath("debug.txt"));
        if (f.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream(&f) << msg << "\n";
        } else {
            std::cout << "Can't append to debug.txt";
            mutex.unlock();
            abort();
        }
    }
    mutex.unlock();
}

/*---------------------------------------------------------------------------*/

int Application::exec(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    qInstallMessageHandler(logHandler);
    qRegisterMetaType<QJSValueList>("QJSValueList");
    qRegisterMetaType<QLinkedList<Node*>>("QLinkedList<Node*>");
    qRegisterMetaType<QVector<NodeStruct>>("QVector<NodeStruct>");
    qmlRegisterType<WindowComponent>("WindowComponent",1,0,"WindowComponent");
    Application a;
    a.installExtension(Extension::TimerExtension);
    a.installExtension(Extension::QuiteExtension);
    a.installExtension(Extension::ConsoleExtension);
    a.installExtension(Extension::DialogExtension);
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
