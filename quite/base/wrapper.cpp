#include "wrapper.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Wrapper::Wrapper(QObject* receiver, QString member)
  : QObject(receiver) {
    qDebug() << "Wrapper ctor";
    _receiver = receiver;
    _member = member.toStdString().c_str();
}

/*---------------------------------------------------------------------------*/

Wrapper::~Wrapper(){
    qDebug() << "Wrapper dtor";
}

/*---------------------------------------------------------------------------*/

void Wrapper::invoke(QJSValueList args) {
    qDebug() << "Wrapper invoke";
    ObjectList list;
    foreach (QJSValue value, args) {
        QSharedPointer<Object> obj = QSharedPointer<Object>(
            new Object(value, _receiver)
        );
        list.append(obj);
    }
    QMetaObject::invokeMethod(_receiver,_member,Q_ARG(ObjectList,list));
}

/*****************************************************************************/

}
}

