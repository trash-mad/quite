#include "windowcomponent.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

WindowComponent::WindowComponent() {
    qDebug() << "WindowComponent ctor";
    connect(&window,SIGNAL(closed()),this,SIGNAL(closed()));
    window.show();
}

/*---------------------------------------------------------------------------*/

WindowComponent::~WindowComponent() {
    qDebug() << "WindowComponent dtor";
}

/*---------------------------------------------------------------------------*/

QQuickItem *WindowComponent::contentItem() const {
    return window.contentItem();
}

/*****************************************************************************/

bool WindowComponentPrivate::event(QEvent *e) {
    if (e->type()==QEvent::Close) {
        emit closed();
    }
    return QQuickWindow::event(e);
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
