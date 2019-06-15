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

void ImportModule::process(
    QObject *engine,
    QJSEngine *eval,
    QThreadPool *pool
) {
    (void)(engine);
    (void)(pool);
    QJSValue module = eval->importModule(path);
    if(module.isError()) {
        qInfo() << "module" << path << "not found";
        eval->throwError(
            QString("MODULE_ERROR %1").arg(
                module.toString()
            )
        );
        eval->evaluate("");
    } else {
        QJSValue res = eval->evaluate("");
        if(res.isError()){
            qInfo() << "module" << path << "syntax error";
            eval->throwError(
                QString("EVAL_ERROR %1").arg(
                    res.toString()
                )
            );
        }
    }
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
