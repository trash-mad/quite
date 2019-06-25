#include "windowmanager.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Component *WindowManager::renderComponent(Node *node) {
    qDebug() << "WindowManager renderComponent";
    Component* component = nullptr;
    switch (node->getType()) {
        case NodeType::Window:
            component = new Components::Window(node);
            break;
        case NodeType::Rectangle:
                //todo
                component = new Components::Window(node);
                break;
        default:
            qCritical() << "WindowManager renderComponent invalid type";
    }
    component->propsChanged(node->getProps());
    return component;
}

/*---------------------------------------------------------------------------*/

Component* WindowManager::renderComponentTree(
    Node *node
) {
    Component *component = nullptr;
    QLinkedList<Component*> child;

    static int count = 0;
    count++;
    if(count==3){
        count = 0;
    }

    if(node->getChild().isEmpty()) {
        component = renderComponent(node);
    } else {
        component = renderComponent(node);
        QLinkedList<Node*> nodes = node->getChild();
        QLinkedList<Node*>::iterator i;
        for (i=nodes.begin(); i!=nodes.end();i++) {
            Node* current = (*i);
            child.append(renderComponentTree(current));
        }
        component->childChanged(child);
    }
    return component;
}

/*---------------------------------------------------------------------------*/

WindowManager::WindowManager(QObject* parent)
  : QObject(parent) {
    qDebug() << "WindowManager ctor";
}

/*---------------------------------------------------------------------------*/

WindowManager::~WindowManager() {
    qDebug() << "WindowManager dtor";
}

/*---------------------------------------------------------------------------*/

void WindowManager::renderUi(Node *root) {
    qDebug() << "WindowManager render";

    if(root->getType()!=NodeType::Window) {
        qCritical() << "WindowManager renderUi rootNode not window";
    } else {
        window = dynamic_cast<Components::Window*>(renderComponentTree(root));
        window->show();
    }

    //emit closed();
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
