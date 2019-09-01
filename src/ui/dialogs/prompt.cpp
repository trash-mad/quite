#include "prompt.h"

namespace Quite {
namespace Ui {
namespace Dialogs {

/*****************************************************************************/

Prompt::Prompt(QString message, QString defaultValue) {
    qDebug() << "Prompt ctor";
    this->defaultValue=defaultValue;
    this->message=message;
}

/*---------------------------------------------------------------------------*/

Prompt::~Prompt() {
    qDebug() << "Prompt dtor";
}

/*---------------------------------------------------------------------------*/

void Prompt::show() {
    bool ok=false;
    QString text=QInputDialog::getText(
        nullptr,
        "App says:",
        message,
        QLineEdit::Normal,
        defaultValue,
        &ok
    );
    if (ok) {
        resolve(text);
    } else {
        resolve("");
    }
}

/*****************************************************************************/

} // namespace Dialogs
} // namespace Ui
} // namespace Quite
