#include "windowmanager.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Component *WindowManager::renderComponent(Node *node, Component* parent) {
    qDebug() << "WindowManager renderComponent";
    Component* component = nullptr;
    switch (node->getType()) {
        case NodeType::Window:
            component = new Components::Window(node, &engine);
            break;
        case NodeType::Rectangle:
            component = new Components::Rectangle(node, &engine, parent);
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

void WindowManager::beforeClose() {
    qDebug() << "WindowManager beforeClose";
    for(int i=wins.length()-1;i!=-1;i--){
        Components::Window* win = wins.at(i);
        wins.removeAt(i);
        delete win;
    }
    emit closed();
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
    qDebug() << "WindowManager render thread" <<QThread::currentThreadId();

    if(root->getType()!=NodeType::Window) {
        qCritical() << "WindowManager renderUi rootNode not window";
    } else {
        Components::Window* w = dynamic_cast<Components::Window*>(
            renderComponentTree(root)
        );
        if(wins.length() == 0) {
            qDebug() << "WindowManager MainWindow created";
            connect(w, SIGNAL(closed()), this, SLOT(beforeClose()));
        }
        wins.append(w);
        w->show();
    }
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
