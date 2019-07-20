#include "window.h"

namespace Quite {
namespace Ui {
namespace Elements {

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

Window::Window(Node *node, QQmlEngine *engine, Element *parent)
  : Element(node, engine, nullptr) {
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
    item = nullptr;
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
