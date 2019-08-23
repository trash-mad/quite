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
        window = qobject_cast<WindowComponent*>(getItem());
        layout = new FlexNode(this,getItem());
        connect(
            window,
            SIGNAL(closed()),
            this,
            SIGNAL(closed())
        );
        connect(
            window,
            SIGNAL(resize()),
            this,
            SLOT(updateLayout())
        );
        /*
         * Default props place
         */
        //window->setProperty("alignItems","center");
        //window->setProperty("justifyContent","center");
    }
}

/*---------------------------------------------------------------------------*/

Window::~Window() {
    qDebug() << "Window dtor";
}

/*---------------------------------------------------------------------------*/

void Window::updateLayout() {
    qDebug() << "Window updateLayout";
    getLayout()->setHeight(window->getHeight());
    getLayout()->setWidth(window->getWidth());
    Element::updateLayout();
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
