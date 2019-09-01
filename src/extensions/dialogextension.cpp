#include "dialogextension.h"

namespace Quite {
namespace Extensions {

/*****************************************************************************/

DialogExtension::DialogExtension(QObject *parent)
  : Extension (parent) {
    qDebug() << "DialogExtension ctor";
}

/*---------------------------------------------------------------------------*/

DialogExtension::~DialogExtension() {
    qDebug() << "DialogExtension dtor";
}

/*---------------------------------------------------------------------------*/

void DialogExtension::install(
    QJSValue global,
    QJSValue current,
    QJSEngine *eval
) {
    qDebug() << "DialogExtension install";
    this->eval=eval;
    global.setProperty("alert",current.property("alert"));
    global.setProperty("prompt",current.property("prompt"));
}

/*---------------------------------------------------------------------------*/

QJSValue DialogExtension::alert(QJSValue msg) {
    qDebug() << "DialogExtension alert" << msg.toString();
    IDialog* dialog=new Alert(msg.toString());
    QCoreApplication::postEvent(parent(),new RenderDialog(dialog));
    QJSValue result=dialog->exec(eval);
    delete dialog;
    return result;
}

/*---------------------------------------------------------------------------*/

QJSValue DialogExtension::prompt(QJSValue msg, QJSValue defaultValue) {
    qDebug() << "DialogExtension prompt" << msg.toString();
    IDialog* dialog=new Prompt(msg.toString(),defaultValue.toString());
    QCoreApplication::postEvent(parent(),new RenderDialog(dialog));
    QJSValue result=dialog->exec(eval);
    delete dialog;
    return result;
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
