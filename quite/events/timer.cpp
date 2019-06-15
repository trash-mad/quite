#include "timer.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

Timer::Timer(
    QTime expired,
    Base::Event* execute,
    bool interval )
  : Base::Event() {
    qDebug() << "Timer ctor";
    this->execute = execute;
    this->interval = interval;
    this->expired = expired;
}

/*---------------------------------------------------------------------------*/

Timer::~Timer() {
    qDebug() << "Timer dtor";
    delete execute;
}

/*---------------------------------------------------------------------------*/

bool Timer::process(QObject *engine, QJSEngine *eval, QThreadPool *pool) {
    if(QTime::currentTime()>expired){
        QCoreApplication::postEvent(engine, execute);
        return true;
    } else {
        //QCoreApplication::postEvent(engine,this);
        return false;
    }
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite


