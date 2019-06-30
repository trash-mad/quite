#include "binder.h"

namespace Quite {
namespace Objects {

/*****************************************************************************/

Binder::Binder(QJSValue func, QJSValue instance, QObject* parent)
  : QObject(parent) {
    qDebug() << "Binder ctor";
    this->instance = instance;
    this->func = func;
}

/*---------------------------------------------------------------------------*/

Binder::~Binder() {
    qDebug() << "Binder dtor";
}

/*---------------------------------------------------------------------------*/

QJSValue Binder::bind(QJSValue func, QJSValue instance, QJSEngine* eval) {
    qDebug() << "Binder bind";
    Binder* binder = new Binder(func, instance);
    return eval->newQObject(binder).property("call");
}

/*---------------------------------------------------------------------------*/

QJSValue Binder::call(
    QJSValue p1,
    QJSValue p2,
    QJSValue p3,
    QJSValue p4,
    QJSValue p5
) {
    qDebug()
        << "Binder call"
        << p1.toString()
        << p2.toString()
        << p3.toString()
        << p4.toString()
        << p5.toString();
    QList<QJSValue> args;
    QJSValue result;
    if (p1.isUndefined()) {
        result = func.callWithInstance(instance);
    } else if (p2.isUndefined()) {
        args << p1;
        result = func.callWithInstance(instance, args);
    } else if(p3.isUndefined()) {
        args << p1;
        args << p2;
        result = func.callWithInstance(instance, args);
    } else if(p4.isUndefined()) {
        args << p1;
        args << p2;
        args << p3;
        result = func.callWithInstance(instance, args);
    } else if(p5.isUndefined()) {
        args << p1;
        args << p2;
        args << p3;
        args << p4;
        result = func.callWithInstance(instance, args);
    } else {
        args << p1;
        args << p2;
        args << p3;
        args << p4;
        args << p5;
        result = func.callWithInstance(instance, args);
    }
    return result;
}

/*****************************************************************************/

} // namespace Objects
} // namespace Quite
