#include "manager.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Element *Manager::renderElement(Node *node, Element *parent) {
    qDebug() << "WindowManager renderComponent";
    Element* element = nullptr;
    NodeType type = node->getType();

    if (type==NodeType::ComponentType) {
         element = renderComponent(node, parent);
    } else {
        if(type==NodeType::WindowType) {
            element = new Window(node, &engine, parent);
        } else if (type==NodeType::RectangleType) {
            element = new Quite::Ui::Elements::Rectangle(node, &engine, parent);
        } else if (type==NodeType::ButtonType) {
            element = new Button(node, &engine, parent);
        } else {
            qCritical() << "Manager can't render node" << type;
        }
        element->propsChanged();
    }
    connect(
        element,
        SIGNAL(eval(Event*)),
        this,
        SIGNAL(eval(Event*))
    );
    return element;
}

/*---------------------------------------------------------------------------*/

Component *Manager::renderComponent(Node* node, Element *parent) {
    Component* component = new Component(
        dynamic_cast<ComponentNode*>(node),
        &engine,
        parent
    );
    connect(
        component,
        SIGNAL(updateSubtree(Node*,Component*)),
        this,
        SLOT(updateSubtree(Node*,Component*))
    );
    return component;
}

/*---------------------------------------------------------------------------*/

Element* Manager::renderElementTree(Node *node, Element* parent) {
    Element* element = nullptr;
    QLinkedList<Element*> child;
    if(node->getChild().isEmpty()) {
        element = renderElement(node, parent);
    } else {
        element = renderElement(node, parent);
        QLinkedList<Node*> nodes = node->getChild();
        QLinkedList<Node*>::iterator i;
        for (i=nodes.begin(); i!=nodes.end();i++) {
            Node* current = (*i);
            child.append(renderElementTree(current, element));
        }
        element->receiveSubtree(child);
    }
    return element;
}

/*---------------------------------------------------------------------------*/

void Manager::updateSubtree(Node* child, Component* that) {
    qDebug() << "WindowManager updateSubtree";
    Element* element = static_cast<Element*>(that);
    that->receiveSubtree(renderElementTree(child, element));
}

/*---------------------------------------------------------------------------*/

Manager::Manager(QObject *parent)
  : QObject(parent){
    qDebug() << "Manager ctor";
    invoker.install(&engine);
}

/*---------------------------------------------------------------------------*/

Manager::~Manager() {
    qDebug() << "Manager dtor";
    if (rootElement!=nullptr) {
        delete rootElement;
    }
}

/*---------------------------------------------------------------------------*/

void Manager::renderUi(Node *root) {
    qDebug() << "WindowManager render thread" <<QThread::currentThreadId();
    if(root->getType()!=NodeType::WindowType) {
        qCritical() << "WindowManager renderUi rootNode not window";
    } else if (rootElement != nullptr) {
        qCritical() << "WindowManager render dublicate";
    } else {
        rootElement = dynamic_cast<Window*>(
            renderElementTree(root)
        );
        connect(rootElement, SIGNAL(closed()), this, SIGNAL(closed()));
        invoker.setRoot(rootElement);
    }
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
