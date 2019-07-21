#include "invoke.h"

namespace Quite {
namespace Objects {

/*****************************************************************************/

Invoke::Invoke(QJSValue func, QJSValue instance) {
    qDebug() << "Invoke ctor";
    this->instance = instance;
    this->func = func;
}

/*---------------------------------------------------------------------------*/

Invoke::~Invoke() {
    qDebug() << "Invoke dtor";
}

/*---------------------------------------------------------------------------*/

Eval *Invoke::createEval(QList<QVariant> args) {
    qDebug() << "Invoke createEval";
    QList<QVariant>::iterator iter;
    for(int i=0;i!=args.length();i++) {
        QVariant value = args.at(i);
        if (value.canConvert<int>()) {
            this->args.append(QJSValue(value.toInt()));
        } else if (value.canConvert<bool>()) {
            this->args.append(QJSValue(value.toBool()));
        } else if (value.canConvert<QString>()) {
            this->args.append(QJSValue(value.toString()));
        } else {
            qCritical() << "Invoke setArgs QVariant invalid type"
                << value.userType();
        }
    }
    return new Eval(func,this->args,instance);
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
