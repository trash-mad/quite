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
    pool = new QThreadPool(this);
    rethrow = new QStack<Monitor*>();
    pool -> setMaxThreadCount(QThread::idealThreadCount());

    QEventLoop loop;
    qDebug() << "Engine event loop started";

    while(true) {
        if(!loop.processEvents()){
            bool wasEmpty = true;
            while(!rethrow->isEmpty()) {
                wasEmpty = false;
                QCoreApplication::postEvent(this, new Await(rethrow->pop()));
            }

            if(wasEmpty) {
                break;
            } else {
                qDebug() << "Engine event loop push monitor";
            }
        }
    }

    qDebug() << "Engine event loop exit";
    emit done();

    eval->deleteLater();
    pool->deleteLater();
    delete rethrow;
}

/*---------------------------------------------------------------------------*/

bool Engine::event(QEvent* e) {
    Event* event = static_cast<Event*>(e);
    switch(event->process(this,eval,pool)){
        case EventResult::AwaiterRethrow:
            rethrow->push(static_cast<Await*>(e)->getMonitor());
            return true;
        default:
            return true;
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
