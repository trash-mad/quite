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
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval))
        ));
    } else if(p3.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval))
        ));
    } else if(p4.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval))
        ));
    } else if(p5.isUndefined()) {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p4,eval))
        ));
    } else {
        check(QMetaObject::invokeMethod(
            origin,
            property.toStdString().c_str(),
            Qt::DirectConnection,
            Q_RETURN_ARG(QJSValue, result),
            Q_ARG(QJSValue, Emitter::fromObject(p1,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p2,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p3,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p4,eval)),
            Q_ARG(QJSValue, Emitter::fromObject(p5,eval))
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
    if(Emitter::engine==nullptr){
        Emitter::engine = engine;
    }

    if(Wrapper::eval==nullptr){
        Wrapper::eval = eval;
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

QJSEngine* Wrapper::eval = nullptr;

/*****************************************************************************/

} // namespace Base
} // namespace Quite
