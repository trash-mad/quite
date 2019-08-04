#include "windowcomponent.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

WindowComponent::WindowComponent() {
    qDebug() << "WindowComponent ctor";
    connect(&window,SIGNAL(closed()),this,SIGNAL(closed()));
    connect(
        &window,
        SIGNAL(beforeRendering()),
        this,
        SLOT(beforeRendering()),
        Qt::DirectConnection
    );
    connect(
        &window,
        SIGNAL(afterRendering()),
        this,
        SLOT(afterRendering()),
        Qt::DirectConnection
    );
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

void WindowComponent::beforeRendering() {
    qDebug() << "WindowComponent beforeRendering exec";
    while (!RenderSynchronizer::instance()->tryBeginRender()) {
        QCoreApplication::processEvents();
        QThread::msleep(40);
    }
    qDebug() << "WindowComponent beforeRendering resolve";
}

/*---------------------------------------------------------------------------*/

void WindowComponent::afterRendering() {
    qDebug() << "WindowComponent afterRendering";
    RenderSynchronizer::instance()->endRender();
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
    } else if (ev->type()==QEvent::UpdateRequest) {
        return RenderSynchronizer::instance()->changesResolved();
    }
    return false;
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
