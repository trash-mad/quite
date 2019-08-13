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
        WindowComponent* window = qobject_cast<WindowComponent*>(getItem());
        connect(
            window,
            SIGNAL(closed()),
            this,
            SIGNAL(closed())
        );
        connect(
            this,
            SIGNAL(update()),
            this,
            SLOT(updateFlexLayout())
        );
    }
}

/*---------------------------------------------------------------------------*/

Window::~Window() {
    qDebug() << "Window dtor";
}

/*---------------------------------------------------------------------------*/

void Window::updateFlexLayout() {
    qDebug() << "Window updateFlexLayout";
    if (DiffCounter::instance()->changesResolved()) {
        qDebug() << "Window updateFlexLayout update";
        //todo: resize
    } else {
        return;
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
