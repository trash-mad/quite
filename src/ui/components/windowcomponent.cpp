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

/*---------------------------------------------------------------------------*/

WindowComponentPrivate::WindowComponentPrivate() {
    installEventFilter(this);
}

/*---------------------------------------------------------------------------*/

bool WindowComponentPrivate::eventFilter(QObject *obj, QEvent *ev) {
    Q_UNUSED(obj);
    if (ev->type()==QEvent::Close) {
        emit closed();
    }
    return false;
}

/*****************************************************************************/

/*bool WindowComponentPrivate::event(QEvent *e) {
    eventMutex.lock();
    if (e->type()==QEvent::Close) {
        emit closed();
    }
    bool result = QQuickWindow::event(e);
    eventMutex.unlock();
    return result;
}*/

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
