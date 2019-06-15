#include "engine.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Engine::Engine(QObject *parent)
  : QThread(parent) {
    qDebug() << "Engine ctor";
    installEventFilter(this);
    moveToThread(this);
}

/*---------------------------------------------------------------------------*/

Engine::~Engine() {
    qDebug() << "Engine dtor";
}

/*---------------------------------------------------------------------------*/

void Engine::run() {

    eval = new QJSEngine(this);
    eval->installExtensions(QJSEngine::Extension::ConsoleExtension);

    pool = new QThreadPool(this);
    pool -> setMaxThreadCount(QThread::idealThreadCount());

    QEventLoop loop;
    qDebug() << "Engine event loop started";
    while(true) {
        if(!loop.processEvents()){
            break;
        }
    }
    qDebug() << "Engine event loop exit";
    emit done();

    eval->deleteLater();
    pool->deleteLater();
}

/*---------------------------------------------------------------------------*/

bool Engine::event(QEvent* e) {
    Event* event = static_cast<Event*>(e);
    if(event) {
        event->process(this,eval,pool);
        return true;
    } else {
        qCritical() << "Engine: invalid event" << e;
        return false;
    }
}

/*---------------------------------------------------------------------------*/

bool Engine::eventFilter(QObject *obj, QEvent *event){
    (void)(obj);
    if (event->type() == Event::staticType()) {
        return false;
    } else {
        return true;
    }
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
