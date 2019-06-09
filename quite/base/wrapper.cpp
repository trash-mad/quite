#include "wrapper.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Wrapper::Wrapper(QObject* receiver, QString member, QObject* engine)
  : QObject(receiver) {
    qDebug() << "Wrapper ctor";
    _receiver = receiver;
    _member = member.toStdString().c_str();
    _engine = engine;
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
            new Object(value, _receiver, _engine)
        );
        list.append(obj);
    }
    QMetaObject::invokeMethod(_receiver,_member,Q_ARG(ObjectList,list));
}

/*****************************************************************************/

}
}

