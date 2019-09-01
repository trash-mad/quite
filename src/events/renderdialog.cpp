#include "renderdialog.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

RenderDialog::RenderDialog(IDialog* dialog) {
    qDebug() << "RenderDialog ctor";
    this->dialog=dialog;
}

/*---------------------------------------------------------------------------*/

IDialog *RenderDialog::getDialog() const {
    return dialog;
}

/*---------------------------------------------------------------------------*/

RenderDialog::~RenderDialog() {
    qDebug() << "RenderDialog dtor";
}

/*---------------------------------------------------------------------------*/

EventResult RenderDialog::process(
    QObject *engine,
    QJSEngine *eval,
    QThreadPool *pool
) {
    qDebug() << "RenderUi process";
    Q_UNUSED(engine);
    Q_UNUSED(eval);
    Q_UNUSED(pool);
    return EventResult::EmitRenderDialog;
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
