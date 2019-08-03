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
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
