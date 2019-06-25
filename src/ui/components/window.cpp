#include "window.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

Window::Window(Node *node)
  : Component(node) {
    qDebug() << "Window ctor";
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
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
