#include "window.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Window::Window(Node *node, QQmlEngine *engine, Element *parent)
  : Element(":/qml/Window.qml", node, engine, nullptr) {
    qDebug() << "Window ctor";
    if(parent!=nullptr) {
        qCritical() << "Window parent must be nullptr";
    } else {
        qDebug() << getItem()->staticMetaObject.className();
        return;
    }
}

/*---------------------------------------------------------------------------*/

Window::~Window() {
    qDebug() << "Window dtor";
}

/*---------------------------------------------------------------------------*/

QQuickItem *Window::getItem() const {
    return Element::getItem();
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
