#include "invoke.h"

namespace Quite {
namespace Objects {

/*****************************************************************************/

Invoke::Invoke(QJSValue func, QJSValue instance)
  : QObject (nullptr) {
    qDebug() << "Invoke ctor";
    this->instance = instance;
    this->func = func;
}

/*---------------------------------------------------------------------------*/

Invoke::~Invoke() {
    qDebug() << "Invoke dtor";
}

/*---------------------------------------------------------------------------*/

Eval *Invoke::createEval() {
    qDebug() << "Invoke createEval";
    QJSValueList args;
    QList<QVariant>::iterator iter;
    for(int i=0;i!=args.length();i++) {
        QVariant value = this->args.at(i);
        if (value.canConvert<int>()) {
            args.append(QJSValue(value.toInt()));
        } else if (value.canConvert<bool>()) {
            args.append(QJSValue(value.toBool()));
        } else if (value.canConvert<QString>()) {
            args.append(QJSValue(value.toString()));
        } else {
            qCritical() << "Invoke setArgs QVariant invalid type"
                << value.userType();
        }
    }
    return new Eval(func,args,instance);
}

/*---------------------------------------------------------------------------*/

void Invoke::addArgs(QList<QVariant> args) {
    qDebug() << "Invoke addArgs";
    this->args=args;
}

/*---------------------------------------------------------------------------*/

bool Invoke::tryCast(QVariant src, Invoke *&dst) {
    if (src.canConvert<QObject*>()) {
        dst=qobject_cast<Invoke*>(qvariant_cast<QObject*>(src));
        return dst!=nullptr;
    } else {
        return false;
    }
}

/*****************************************************************************/

} // namespace Objects
} // namespace Quite
