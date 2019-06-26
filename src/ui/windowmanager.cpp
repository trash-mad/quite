#include "windowmanager.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Component *WindowManager::renderComponent(Node *node, Component* parent) {
    qDebug() << "WindowManager renderComponent";
    Component* component = nullptr;
    switch (node->getType()) {
        case NodeType::Window:
            component = new Components::Window(node, &engine, parent);
            break;
        case NodeType::Rectangle:
            component = new Components::Rectangle(node, &engine, parent);
            break;
        case NodeType::Button:
            component = new Components::Button(node, &engine, parent);
            break;
        default:
            qCritical() << "WindowManager renderComponent invalid type";
    }
    component->propsChanged(node->getProps());
    return component;
}

/*---------------------------------------------------------------------------*/

Component* WindowManager::renderComponentTree(
    Node* node,
    Component* parent
) {
    Component *component = nullptr;
    QLinkedList<Component*> child;
    if(node->getChild().isEmpty()) {
        component = renderComponent(node, parent);
    } else {
        component = renderComponent(node, parent);
        QLinkedList<Node*> nodes = node->getChild();
        QLinkedList<Node*>::iterator i;
        for (i=nodes.begin(); i!=nodes.end();i++) {
            Node* current = (*i);
            child.append(renderComponentTree(current, component));
        }
        component->childChanged(child);
    }
    return component;
}

/*---------------------------------------------------------------------------*/

WindowManager::WindowManager(QObject* parent)
  : QObject(parent) {
    qDebug() << "WindowManager ctor";
    invoker.install(&engine);
}

/*---------------------------------------------------------------------------*/

WindowManager::~WindowManager() {
    qDebug() << "WindowManager dtor";
    delete window;
}

/*---------------------------------------------------------------------------*/

void WindowManager::renderUi(Node *root) {
    qDebug() << "WindowManager render thread" <<QThread::currentThreadId();
    if(root->getType()!=NodeType::Window) {
        qCritical() << "WindowManager renderUi rootNode not window";
    } else if(window != nullptr) {
        qCritical() << "WindowManager render dublicate";
    } else {
        window = dynamic_cast<Components::Window*>(
            renderComponentTree(root)
        );
        connect(window, SIGNAL(closed()), this, SIGNAL(closed()));
        invoker.setRoot(window);
        window->show();
    }
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
