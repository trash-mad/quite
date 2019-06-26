#include "window.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

bool WindowPrivate::event(QEvent *e) {
    if (e->type() == QEvent::Close) {
        emit closed();
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

WindowPrivate::~WindowPrivate() {
    qDebug() << "WindowPrivate dtor";
}

/*****************************************************************************/

Window::Window(Node *node, QQmlEngine* engine)
  : Component(node, engine, nullptr) {
    qDebug() << "Window ctor";
    connect(&window, SIGNAL(closed()), this, SIGNAL(closed()));
    item = window.contentItem();
    window.show();
}

/*---------------------------------------------------------------------------*/

Window::~Window() {
    qDebug() << "Window dtor";
}

/*---------------------------------------------------------------------------*/

void Window::show() {
    qDebug() << "Window show";
    window.show();
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
