#include "window.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

bool WindowPrivate::event(QEvent *e) {
    if (e->type() == QEvent::Close) {
        emit closed();
        hide();
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

Window::Window(Node *node)
  : Component(node) {
    qDebug() << "Window ctor";
    connect(&window,SIGNAL(closed()),this,SIGNAL(closed()));
    item = window.contentItem();
    window.show();
}

/*---------------------------------------------------------------------------*/

Window::~Window() {
    qDebug() << "Window dtor";
}

/*---------------------------------------------------------------------------*/

void Window::propsChanged(QMap<QString, QVariant> props) {
    qDebug() << "Window propsChanged";
    (void)(props);
}

/*---------------------------------------------------------------------------*/

void Window::childChanged(QLinkedList<Component*> child) {
    qDebug() << "Window childChanged";
    (void)(child);
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
