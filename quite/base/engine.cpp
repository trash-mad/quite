#include "engine.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Engine::Engine(QObject *parent)
  : QThread(parent) {
    qDebug() << "Engine ctor";
    installEventFilter(this);
    _initialThread = QThread::currentThread();
    _eval = new QJSEngine(this);
    _pool = new QThreadPool(this);
    _pool -> setMaxThreadCount(QThread::idealThreadCount());
    moveToThread(this);
}

/*---------------------------------------------------------------------------*/

Engine::~Engine() {
    qDebug() << "Engine dtor";
    _eval -> deleteLater();
    _pool -> deleteLater();
}

/*---------------------------------------------------------------------------*/

QJSValue Engine::fromQObject(QObject *obj) {
    QJSValue object = _eval->newQObject(obj);
    QJSValue result = _eval->newObject();
    QJSValueIterator it(object);
    while (it.hasNext()) {
        it.next();
        if(it.value().isCallable()){
            Wrapper* wrapper = new Wrapper(obj, it.name());
            QJSValue temp = _eval->newQObject(wrapper);
            QJSValue property = temp.property("invoke");
            result.setProperty(it.name(), property);
        }
    }
    return result;
}

/*---------------------------------------------------------------------------*/

void Engine::run() {
    QEventLoop loop;
    qDebug() << "Engine: event loop started";
    loop.processEvents(QEventLoop::AllEvents);
    qDebug() << "Engine: event loop exit";
    moveToThread(_initialThread);
    _eval->moveToThread(_initialThread);
    _pool->moveToThread(_initialThread);
    emit done();
}

/*---------------------------------------------------------------------------*/

bool Engine::event(QEvent *event) {
    /*qDebug()
        << "Engine:"
        << "event="  << event->type()
        << "thread=" << QThread::currentThreadId();*/
    return true;
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

}
}
