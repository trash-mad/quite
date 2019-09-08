#include "dialog.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

IDialog::~IDialog(){}

/*****************************************************************************/

DialogResolver::DialogResolver(QObject *parent)
  : QObject(parent) {
    qDebug() << "DialogResolver ctor";
}

/*---------------------------------------------------------------------------*/

DialogResolver::~DialogResolver() {
    qDebug() << "DialogResolver dtor";
}

/*---------------------------------------------------------------------------*/

void DialogResolver::resolve(QVariant result) {
    this->result=result;
    emit resolved();
}

/*---------------------------------------------------------------------------*/

QVariant DialogResolver::getResult() const {
    return result;
}

/*****************************************************************************/

template<typename ReturnValue>
Dialog<ReturnValue>::Dialog() {
    qDebug() << "Dialog ctor";
    resultType=qRegisterMetaType<ReturnValue>();
}

/*---------------------------------------------------------------------------*/

template<typename ReturnValue>
Dialog<ReturnValue>::~Dialog() {
    qDebug() << "Dialog dtor";
}

/*---------------------------------------------------------------------------*/

template<typename ReturnValue>
QJSValue Dialog<ReturnValue>::exec(
    QJSEngine* engine
) {
    qDebug() << "Dialog exec";
    QEventLoop loop;
    QObject::connect(&resolver,SIGNAL(resolved()),&loop,SLOT(quit()));
    loop.exec();
    qDebug() << "Dialog exec resolve";
    QVariant result=resolver.getResult();
    if (result.canConvert(resultType)) {
        return engine->toScriptValue(result);
    } else {
        qCritical() << "Dialog exec can't cast result type";
        return QJSValue();
    }
}

/*---------------------------------------------------------------------------*/

template<typename ReturnValue>
void Dialog<ReturnValue>::resolve(ReturnValue result) {
    qDebug() << "Dialog resolve";
    resolver.resolve(QVariant::fromValue(result));
}

/*****************************************************************************/

template class Dialog<QString>;

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
