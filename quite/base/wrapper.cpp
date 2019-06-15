#include "wrapper.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

void Wrapper::check(bool found) {
    if(!found){
        qCritical() << "Wrapper" << property << "invalid params";
    }
}

/*---------------------------------------------------------------------------*/

Wrapper::Wrapper(QObject* origin, QString property)
  : QObject(origin) {
    qDebug() << "Wrapper ctor";
    this->origin = origin;
    this->property = property;
}

/*---------------------------------------------------------------------------*/

Wrapper::~Wrapper() {
    qDebug() << "Wrapper dtor";
}

QJSValue Wrapper::call(
    QJSValue p1,
    QJSValue p2,
    QJSValue p3,
    QJSValue p4,
    QJSValue p5
) {
    qDebug() << "Wrapper call";
    QJSValue result;
    if(p1.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result)
        ));
    } else if(p2.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, p1)
        ));
    } else if(p3.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, p1),
            Q_ARG(QJSValue, p2)
        ));
    } else if(p4.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, p1),
            Q_ARG(QJSValue, p2),
            Q_ARG(QJSValue, p3)
        ));
    } else if(p5.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, p1),
            Q_ARG(QJSValue, p2),
            Q_ARG(QJSValue, p3),
            Q_ARG(QJSValue, p4)
        ));
    } else {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, p1),
            Q_ARG(QJSValue, p2),
            Q_ARG(QJSValue, p3),
            Q_ARG(QJSValue, p4),
            Q_ARG(QJSValue, p5)
        ));
    }
    return result;
}

/*---------------------------------------------------------------------------*/

QJSValue Wrapper::fromQObject(
    QObject *engine,
    QObject *obj,
    QJSEngine *eval
) {
    if(Wrapper::engine==nullptr){
        Wrapper::engine = engine;
    }

    QJSValue object = eval->newQObject(obj);
    QJSValue result = eval->newObject();
    QJSValueIterator it(object);

    while (it.hasNext()) {
        it.next();

        if(it.value().isCallable()) {
            Wrapper* wrapped = new Wrapper(obj, it.name());
            QJSValue managed = eval->newQObject(wrapped);
            result.setProperty(it.name(),managed.property("call"));
        }

    }
    return result;
}

/*---------------------------------------------------------------------------*/

QObject* Wrapper::engine = nullptr;

/*****************************************************************************/

} // namespace Base
} // namespace Quite
