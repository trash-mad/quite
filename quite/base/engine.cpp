#include "engine.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Engine::Engine(QObject *parent)
  : QThread(parent) {
    qDebug() << "Engine ctor";
    installEventFilter(this);
    initialThread = QThread::currentThread();
    eval = new QJSEngine(this);
    pool = new QThreadPool(this);
    pool -> setMaxThreadCount(QThread::idealThreadCount());
    moveToThread(this);
}

/*---------------------------------------------------------------------------*/

Engine::~Engine() {
    qDebug() << "Engine dtor";
    eval -> deleteLater();
    pool -> deleteLater();
}

/*---------------------------------------------------------------------------*/

void Engine::run() {
    QEventLoop loop;
    qDebug() << "Engine: event loop started";
    loop.processEvents(QEventLoop::AllEvents);
    qDebug() << "Engine: event loop exit";
    moveToThread(initialThread);
    eval->moveToThread(initialThread);
    pool->moveToThread(initialThread);
    emit done();
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
