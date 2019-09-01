#include "alert.h"

namespace Quite {
namespace Ui {
namespace Dialogs {

/*****************************************************************************/

Alert::Alert(QString text) {
    qDebug() << "Alert ctor";
    this->text=text;
}

/*---------------------------------------------------------------------------*/

Alert::~Alert() {
    qDebug() << "Alert dtor";
}

/*---------------------------------------------------------------------------*/

void Alert::show() {
    /*
     * QWidget lives in the thread where the new operator was applied
     */
    QMessageBox* msg=new QMessageBox();
    msg->setText(text);
    msg->exec();
    resolve("");
    delete msg;
}

/*****************************************************************************/

} // namespace Dialogs
} // namespace Ui
} // namespace Quite
