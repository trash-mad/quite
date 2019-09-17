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

QtMessageHandler Application::createLogHandler(bool verbose, QDir d) {
    static QDir dir = d;
    if (verbose) {
        return [](QtMsgType t, const QMLC &ctx, const QString &msg) {
            Q_UNUSED(ctx)
            static QMutex mutex;
            mutex.lock();
            if(t == QtMsgType::QtInfoMsg) {
                std::cout << msg.toStdString() << "\n";
            } else if (t == QtMsgType::QtCriticalMsg) {
                std::cout << msg.toStdString() << "\n";
                mutex.unlock();
                abort();
            } else {
                QFile f(dir.filePath("debug.txt"));
                if (f.open(QIODevice::WriteOnly | QIODevice::Append)) {
                    QTextStream(&f) << msg << "\n";
                } else {
                    std::cout << "Can't append to debug.txt";
                    mutex.unlock();
                    abort();
                }
            }
            mutex.unlock();
        };
    } else {
        return [](QtMsgType t, const QMLC &ctx, const QString &msg) {
            Q_UNUSED(ctx)
            if (t == QtMsgType::QtCriticalMsg) {
                std::cout << msg.toStdString() << "\n";
                abort();
            }
        };
    }
}

/*---------------------------------------------------------------------------*/

int Application::exec(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QDir dir=QDir::current();

    app.setQuitOnLastWindowClosed(false);
    qRegisterMetaType<QJSValueList>("QJSValueList");
    qRegisterMetaType<QLinkedList<Node*>>("QLinkedList<Node*>");
    qRegisterMetaType<QVector<NodeStruct>>("QVector<NodeStruct>");
    qmlRegisterType<WindowComponent>("WindowComponent",1,0,"WindowComponent");
    qmlRegisterSingletonType(
        "ConsoleProvider",
        1, 0,
        "Console",
        ConsoleProvider::initSingletonType
    );

    QCommandLineParser parser;

    QCommandLineOption verbose({"v","verbose"},"print runtime information");
    QCommandLineOption debug({"d","debug"},"open debug console");

    parser.addPositionalArgument("path","main.js entry path");

    parser.addOptions({debug,verbose});
    parser.parse(QCoreApplication::arguments());

    /*
     * Parse app working dir from console arguments
     */
    const QStringList positionalArguments = parser.positionalArguments();
    if (positionalArguments.isEmpty()) {
        dir=QDir::current();
    } else {
        QFile file(positionalArguments.first());
        QFileInfo info(file);
        if (!info.exists()) {
            std::cout << "invalid path parameter" << std::endl;
        } else if (info.isDir()) {
            dir=QDir(info.absoluteFilePath());
        } else if (info.isFile()) {
            dir=info.dir();
        }
    }

    qInstallMessageHandler(createLogHandler(
        parser.isSet(verbose),
        dir
    ));

    /*todo: if (parser.isSet(debug)) {
        qInfo() << "debug";
    }*/

    Application a;
    a.installExtension(Extension::TimerExtension);
    a.installExtension(Extension::QuiteExtension);
    a.installExtension(Extension::ConsoleExtension);
    a.installExtension(Extension::DialogExtension);
    a.importModule(dir.filePath("main.js"));

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
