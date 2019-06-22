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
    qDebug() << "Window appendchild";
    child->getNode()->setParentItem(node);
}

/*---------------------------------------------------------------------------*/

void Window::removeChild(Node *child) {
    qDebug() << "Window removeChild";
    node->childItems().removeOne(child->getNode());
}

/*---------------------------------------------------------------------------*/

void Window::insertBefore(Node *child, Node *beforeChild) {
    qDebug() << "Window insertBefore";
    node->childItems().insert(
        node->childItems().indexOf(beforeChild->getNode()),
        child->getNode()
    );
}

/*---------------------------------------------------------------------------*/

void Window::commitUpdate(QMap<QString, QVariant> props) {
    qDebug() << "Rectangle commitUpdate";
    (void)(props);
}

/*---------------------------------------------------------------------------*/

Window::Window(QObject *parent, QQmlEngine* engine)
  : Node(parent, engine) {
    qDebug() << "Window ctor";
    window = new WindowPrivate();
    node = window->contentItem();
}

/*---------------------------------------------------------------------------*/

Window::~Window() {
    qDebug() << "Window dtor";
    window->deleteLater();
}

/*---------------------------------------------------------------------------*/

bool Window::isClosed() const {
    return window->isClosed();
}

/*---------------------------------------------------------------------------*/

bool Window::isOpened() const {
    return window->isClosed();
}

/*---------------------------------------------------------------------------*/

void Window::show() {
    window->show();
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
