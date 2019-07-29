#include "importmodule.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

ImportModule::ImportModule(QString path)
  : Event() {
    qDebug() << "ImportModule ctor";
    this->path = path;
}

/*---------------------------------------------------------------------------*/

ImportModule::~ImportModule() {
    qDebug() << "ImportModule dtor";
}

/*---------------------------------------------------------------------------*/

EventResult ImportModule::process(
    QObject *engine,
    QJSEngine *eval,
    QThreadPool *pool
) {
    (void)(engine);
    (void)(pool);
    QJSValue module = eval->importModule(QDir::current().filePath(path));
    if (!QFile::exists(QDir::current().filePath(path))) {
        qInfo()
            << "module"
            << QDir::current().filePath(path)
            << "not exist";
    } else if(module.isError()) {
        qInfo()
            << "module"
            << QDir::current().filePath(path)
            << "syntax error";
        eval->throwError(
            QString("MODULE_ERROR %1").arg(
                module.toString()
            )
        );
    } else {
        QJSValue res = eval->evaluate("");
        if(res.isError()){
            qInfo() << "module" << path << "eval error";
            eval->throwError(
                QString("EVAL_ERROR %1").arg(
                    res.toString()
                )
            );
        }
    }

    return EventResult::Ok;
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
