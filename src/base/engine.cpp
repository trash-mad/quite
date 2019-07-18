#include "engine.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Engine::Engine(QObject *parent)
  : QThread(parent) {
    qDebug() << "Engine ctor";
    //installEventFilter(this);
    moveToThread(this);
}

/*---------------------------------------------------------------------------*/

Engine::~Engine() {
    qDebug() << "Engine dtor";
}

/*---------------------------------------------------------------------------*/

void Engine::run() {

    qDebug() << "Engine thread" <<QThread::currentThreadId();

    eval = new QJSEngine(this);
    pool = new QThreadPool(this);
    rethrow = new QStack<Monitor*>();
    pool -> setMaxThreadCount(QThread::idealThreadCount());

    eval->globalObject().setProperty(
        "global",
        eval->globalObject().prototype()
    );

    eval->installExtensions(QJSEngine::Extension::GarbageCollectionExtension);

    QEventLoop loop;
    qDebug() << "Engine event loop started";

    while(true) {
        if(!loop.processEvents()) {
            bool continueLoop = uiexec;
            while(!rethrow->isEmpty()) {
                continueLoop = continueLoop || false;
                QCoreApplication::postEvent(this, new Await(rethrow->pop()));
            }
            if(!continueLoop) {
                qDebug() << "Engine event loop free";
                break;
            } else {
                QThread::msleep(25);
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
    if(e->type() == Event::staticType()) {
        Event* event = static_cast<Event*>(e);
        switch(event->process(this,eval,pool)){
            case EventResult::AwaiterRethrow:
                rethrow->push(static_cast<Await*>(e)->getMonitor());
                return true;
            case EventResult::EmitRenderUi:
                uiexec = true;
                emit renderUi(static_cast<RenderUi*>(e)->getRootNode());
                return true;
            default:
                return true;
        }
    } else {
        return QObject::event(e);
    }
}

/*---------------------------------------------------------------------------*/

void Engine::windowClosed() {
    qDebug() << "Engine windowClosed";
    uiexec = false;
}

/*---------------------------------------------------------------------------*/

void Engine::evalFunc(QJSValue func, QJSValueList args) {
    qDebug() << "Engine eval";
    QCoreApplication::postEvent(this, new Events::Eval(func, args));
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
