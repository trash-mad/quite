#include "rendersynchronizer.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

RenderSynchronizer::RenderSynchronizer() {
    qDebug() << "RenderSynchronizer ctor";
}

/*---------------------------------------------------------------------------*/

RenderSynchronizer::~RenderSynchronizer() {
    qDebug() << "RenderSynchronizer dtor";
}

/*---------------------------------------------------------------------------*/

bool RenderSynchronizer::tryIncrementCounter(QString from) {
    qDebug() << "RenderSynchronizer tryIncrementCounter from"
        << from << "counter" << resolveCounter;
    locker.lock();
    bool result;
    if (rendering) {
        result=false;
    } else {
        resolveCounter++;
        result=true;
    }
    locker.unlock();
    return result;
}

/*---------------------------------------------------------------------------*/

void RenderSynchronizer::decrementCounter(QString from) {
    qDebug() << "RenderSynchronizer decrementCounter from"
        <<from<<"counter"<<resolveCounter;
    locker.lock();
    if (resolveCounter==0) {
        qCritical() << "RenderSynchronizer decrementCounter < 0";
    } else {
        resolveCounter--;
    }
    locker.unlock();
}

/*---------------------------------------------------------------------------*/

bool RenderSynchronizer::tryBeginRender() {
    qDebug() << "RenderSynchronizer tryBeginRender"<<resolveCounter;
    locker.lock();
    bool result;
    if (resolveCounter==0) {
        rendering=true;
        result=true;
    } else {
        result=false;
    }
    locker.unlock();
    return result;
}

/*---------------------------------------------------------------------------*/

void RenderSynchronizer::endRender() {
    qDebug() << "RenderSynchronizer endRender"<<resolveCounter;
    locker.lock();
    rendering=false;
    locker.unlock();
}

/*---------------------------------------------------------------------------*/

bool RenderSynchronizer::changesResolved() {
    qDebug() << "RenderSynchronizer changesResolved";
    locker.lock();
    bool result = resolveCounter==0;
    locker.unlock();
    return result;
}

/*---------------------------------------------------------------------------*/

RenderSynchronizer* RenderSynchronizer::instance() {
    static RenderSynchronizer synchr;
    return std::addressof(synchr);
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
