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
        connect(
            window,
            SIGNAL(resize()),
            this,
            SLOT(updateFlexLayout())
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

FlexNode *Window::buildFlexTree(Element *current) {
    FlexNode* node = new FlexNode(current->getItem());
    QLinkedList<Element*> child=current->getChild();
    QLinkedList<Element*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        node->appendChild(buildFlexTree(*iter));
    }
    return node;
}

/*---------------------------------------------------------------------------*/

void Window::startFlexLayout() {
    qDebug() << "Window startFlexLayout";
}

/*---------------------------------------------------------------------------*/

void Window::updateFlexLayout() {
    qDebug() << "Window updateFlexLayout";
    if (!DiffCounter::instance()->changesResolved()) {
        qDebug() << "Window updateFlexLayout not ready";
    } else {
        qDebug() << "Window updateFlexLayout ready";
        FlexNode* rootNode = buildFlexTree(this);
        rootNode->printTree();
        rootNode->buildTree();
        rootNode->calculateLayoutLtr();
        rootNode->deleteLater();
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
