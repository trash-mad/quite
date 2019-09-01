#include "dialog.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

template class Dialog<QString>;

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
    QJSEngine* engine,
    QJSValue callBack
) {
    qDebug() << "Dialog exec";
    /*
     * Асинхронные диалоги переопределяют метод exec
     * реализуя интерфейс IDialog повторно с использованием
     * параметра callBack.
     *
     * Emitter перенаправит вызов и всё нормально отработает (должно)
     */
    Q_UNUSED(callBack);
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

IDialog::~IDialog(){}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
