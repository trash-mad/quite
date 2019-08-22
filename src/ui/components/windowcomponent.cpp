#include "windowcomponent.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

WindowComponent::WindowComponent() {
    qDebug() << "WindowComponent ctor";
    window=new WindowComponentPrivate();
    setParentItem(window->contentItem());
    connect(window,SIGNAL(closed()),this,SIGNAL(closed()));
    connect(window,SIGNAL(resize()),this,SIGNAL(resize()));
    window->show();
}

/*---------------------------------------------------------------------------*/

WindowComponent::~WindowComponent() {
    qDebug() << "WindowComponent dtor";
    window->deleteLater();
}

/*---------------------------------------------------------------------------*/

int WindowComponent::getHeight() const {
    return window->size().height();
}

/*---------------------------------------------------------------------------*/

int WindowComponent::getWidth() const {
    return window->size().width();
}

/*****************************************************************************/

WindowComponentPrivate::WindowComponentPrivate() {
    installEventFilter(this);
}

/*---------------------------------------------------------------------------*/

bool WindowComponentPrivate::eventFilter(QObject *obj, QEvent *ev) {
    Q_UNUSED(obj);
    if (ev->type()==QEvent::Close) {
        emit closed();
    } else if (ev->type()==QEvent::Resize) {
        emit resize();
    }
    return false;
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
