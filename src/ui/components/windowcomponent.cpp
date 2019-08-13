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
    connect(window,SIGNAL(resize(int,int)),this,SLOT(resizeHandler(int,int)));
    window->show();
    setProperty("height", window->size().height());
    setProperty("width", window->size().width());
}

/*---------------------------------------------------------------------------*/

WindowComponent::~WindowComponent() {
    qDebug() << "WindowComponent dtor";
    window->deleteLater();
}

/*---------------------------------------------------------------------------*/

void WindowComponent::resizeHandler(int height, int width) {
    qDebug() << "WindowComponent resize";
    setProperty("height",height);
    setProperty("width", width);
    emit resize();
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
        QSize size = static_cast<QResizeEvent*>(ev)->size();
        emit resize(size.height(),size.width());
    }
    return false;
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
