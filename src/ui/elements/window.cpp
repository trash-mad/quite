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

FlexNode *Window::buildFlexTree(Element *current,bool fill) {
    FlexNode* node = new FlexNode(current->getItem(),fill);
    QLinkedList<Element*> child=current->getChild();
    QLinkedList<Element*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        node->appendChild(buildFlexTree(
            *iter,
            qobject_cast<Component*>(current)!=nullptr
        ));
    }
    return node;
}

/*---------------------------------------------------------------------------*/

void Window::updateFlexLayout() {
    qDebug() << "Window updateFlexLayout";
    if (!DiffCounter::instance()->changesResolved()) {
        qDebug() << "Window updateFlexLayout not ready";
    } else {
        qDebug() << "Window updateFlexLayout ready";
        FlexNode* windowNode;
        {
            windowNode = new FlexNode(
                getItem(),
                window->getHeight(),
                window->getWidth()
            );
            QLinkedList<Element*> child=getChild();
            QLinkedList<Element*>::iterator iter;
            for (iter=child.begin();iter!=child.end();iter++) {
                windowNode->appendChild(buildFlexTree(
                    *iter,
                    qobject_cast<Component*>(*iter)!=nullptr
                ));
            }
        }
        windowNode->printTree();
        windowNode->buildTree();
        windowNode->calculateLayoutLtr();
        windowNode->deleteLater();
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
