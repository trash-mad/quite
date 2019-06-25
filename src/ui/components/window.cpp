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

Window::Window(Node *node, QQmlEngine* engine)
  : Component(node, engine) {
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
    QLinkedList<Component*>::iterator i;
    for (i=child.begin(); i!=child.end();i++) {
        Component* component = (*i);
        component->getItem()->setParentItem(item);
    }
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
