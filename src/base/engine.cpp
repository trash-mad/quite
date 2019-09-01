#include "engine.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Engine::Engine(QObject *parent)
  : QThread(parent) {
    qDebug() << "Engine ctor";
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
    connect(qApp,SIGNAL(aboutToQuit()),&loop,SLOT(quit()));
    qDebug() << "Engine event loop started";

    while(true) {
        if(!loop.processEvents()) {
            if (qApp->closingDown()) {
                terminate();
            } else {
                bool continueLoop = uiexec;
                while(!rethrow->isEmpty()) {
                    //continueLoop = continueLoop || false;
                    QCoreApplication::postEvent(
                        this,
                        new Await(rethrow->pop())
                    );
                }
                if(!continueLoop) {
                    qDebug() << "Engine event loop free";
                    break;
                } else {
                    QThread::msleep(25);
                }
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
    if (qApp->closingDown()) {
        return QObject::event(e);
    } else if (e->type() == Event::staticType()) {
        Event* event = static_cast<Event*>(e);
        switch(event->process(this,eval,pool)){
            case EventResult::AwaiterRethrow:
                rethrow->push(static_cast<Await*>(e)->getMonitor());
                return true;
            case EventResult::EmitRenderUi:
                uiexec = true;
                emit renderUi(static_cast<RenderUi*>(e)->getRootNode());
                return true;
            case EventResult::EmitRenderDialog:
                emit renderDialog(static_cast<RenderDialog*>(e)->getDialog());
                return true;
            default:
                return true;
        }
    } else {
        return QObject::event(e);
    }
}

/*---------------------------------------------------------------------------*/

void Engine::invokeHandler(Invoke* o) {
    qDebug() << "Engine invokeHandler";
    QCoreApplication::postEvent(this, o->createEval());
}

/*---------------------------------------------------------------------------*/

void Engine::windowClosed() {
    qDebug() << "Engine windowClosed";
    uiexec=false;
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
