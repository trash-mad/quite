#include "window.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

bool WindowPrivate::isClosed() const {
    return closed;
}

/*---------------------------------------------------------------------------*/

bool WindowPrivate::isOpened() const {
    return opened;
}

/*---------------------------------------------------------------------------*/

bool WindowPrivate::event(QEvent *e) {
    if (e->type() == QEvent::Show) {
        opened = true;
        return QQuickWindow::event(e);
    } else if (e->type() == QEvent::Close) {
        closed = true;
        return true;
    } else {
        return QQuickWindow::event(e);
    }
}

/*---------------------------------------------------------------------------*/

WindowPrivate::WindowPrivate() {
    qDebug() << "WindowPrivate ctor";
}

/*---------------------------------------------------------------------------*/

WindowPrivate::~WindowPrivate(){
    qDebug() << "WindowPrivate dtor";
}

/*****************************************************************************/

void Window::appendChild(Node *child) {
    qCritical() << "Window not implemented";
}

/*---------------------------------------------------------------------------*/

void Window::removeChild(Node *child) {
    qCritical() << "Window not implemented";
}

/*---------------------------------------------------------------------------*/

void Window::insertBefore(Node *child, Node *beforeChild) {
    qCritical() << "Window not implemented";
}

/*---------------------------------------------------------------------------*/

void Window::commitUpdate(QMap<QString, QVariant> props) {
    qCritical() << "Window not implemented";
}

/*---------------------------------------------------------------------------*/

Window::Window(QObject *parent, QQmlEngine* engine)
  : Node(parent, engine) {
    qDebug() << "Window ctor";
}

/*---------------------------------------------------------------------------*/

Window::~Window() {
    qDebug() << "Window dtor";
}

/*---------------------------------------------------------------------------*/

bool Window::isClosed() const {
    return window.isClosed();
}

/*---------------------------------------------------------------------------*/

bool Window::isOpened() const {
    return window.isClosed();
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
