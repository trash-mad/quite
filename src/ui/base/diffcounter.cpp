#include "diffcounter.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

DiffCounter::DiffCounter() {
    qDebug() << "DiffCounter ctor";
}

/*---------------------------------------------------------------------------*/

DiffCounter::~DiffCounter() {
    qDebug() << "DiffCounter dtor";
}

/*---------------------------------------------------------------------------*/

bool DiffCounter::tryIncrementCounter() {
    qDebug() << "DiffCounter tryIncrementCounter" << resolveCounter;
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

void DiffCounter::decrementCounter() {
    qDebug() << "DiffCounter decrementCounter" << resolveCounter;
    locker.lock();
    if (resolveCounter==0) {
        qCritical() << "DiffCounter decrementCounter < 0";
    } else if (resolveCounter==1) {
        resolveCounter--;
        /* Нужен асинхронных запуск, чтобы разблокировать мьютекс */
        QMetaObject::invokeMethod(
            this,
            "diffFree",
            Qt::QueuedConnection
        );
    } else {
        resolveCounter--;
    }
    locker.unlock();
}

/*---------------------------------------------------------------------------*/

/*
 * Будьте очень осторожны, используя эти методы! ComponentNode реализует
 * ожидание с использованием while(true){ ... processEvents()}
 * Как следствие, второй цикл while создаст deadlock. Чтобы избежать,
 * применяйте в одном слоте сразу и tryBegin и end, а слот вызывайте через
 * таймер!
 */
bool DiffCounter::tryBeginRender() {
    qDebug() << "DiffCounter tryBeginRender"<<resolveCounter;
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

void DiffCounter::endRender() {
    qDebug() << "DiffCounter endRender"<<resolveCounter;
    locker.lock();
    if (rendering) {
        rendering=false;
    } else {
        qCritical() << "DiffCounter render not started";
    }
    locker.unlock();
}

/*---------------------------------------------------------------------------*/

bool DiffCounter::changesResolved() {
    qDebug() << "DiffCounter changesResolved";
    locker.lock();
    bool result = resolveCounter==0;
    locker.unlock();
    return result;
}

/*---------------------------------------------------------------------------*/

DiffCounter* DiffCounter::instance() {
    static DiffCounter synchr;
    return std::addressof(synchr);
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
