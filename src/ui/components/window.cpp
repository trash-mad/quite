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

Window::Window(Node *node, QQmlEngine* engine, Component* parent)
  : Component(node, engine, nullptr) {
    qDebug() << "Window ctor";
    if(parent!=nullptr) {
        qCritical() << "Window parent must be nullptr";
    } else {
        connect(&window, SIGNAL(closed()), this, SIGNAL(closed()));
        item = window.contentItem();
        window.show();
    }
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

/*---------------------------------------------------------------------------*/

void Window::invoke(QString type, QVariant p1, QVariant p2, QVariant p3) {
    (void)(type);
    (void)(p1);
    (void)(p2);
    (void)(p3);
    qCritical() << "Window invoke not implemented";
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
