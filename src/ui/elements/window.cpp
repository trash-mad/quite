#include "window.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Window::Window(Node *node, QQmlEngine *engine, Element *parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Window.qml")),
        node,
        engine,
        nullptr
    ) {
    qDebug() << "Window ctor";
    if(parent!=nullptr) {
        qCritical() << "Window parent must be nullptr";
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

Window::~Window() {
    qDebug() << "Window dtor";
    /*
     * Перед крашем пишется единственный Window dtor.
     * Кажется, QQuickItem::polishItems() не при чем и дело в
     * JS garbage collector
     *
     */
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
