#include "manager.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Element *Manager::renderElement(Node *node, Element *parent) {
    qDebug() << "WindowManager renderComponent";
    Element* element = nullptr;
    NodeType type = node->getEnumType();
    if (type==NodeType::ComponentType) {
         element = renderComponent(node, parent);
    } else if (type==NodeType::WindowType) {
        element = renderWindow(node, parent);
    } else {
        switch (type) {
            case NodeType::RectangleType:
                element = new Quite::Ui::Elements::Rectangle(
                    node,
                    &engine,
                    parent
                );
                break;
            case NodeType::ButtonType:
                element = new Button(node, &engine, parent);
                break;
            case NodeType::ScrollViewerType:
                element = new ScrollViewer(node,&engine,parent);
                break;
            case NodeType::CheckBoxType:
                element = new CheckBox(node,&engine,parent);
                break;
            case NodeType::EntryType:
                element = new Entry(node, &engine, parent);
                break;
            case NodeType::LabelType:
                element = new Label(node, &engine, parent);
                break;
            default:
                qCritical() << "Manager can't render node" << type;
        }
    }
    while (!DiffCounter::instance()->tryIncrementCounter()) {
        QCoreApplication::processEvents();
        QThread::msleep(50);
    }
    QMetaObject::invokeMethod(
        node,
        "commitProps",
        Qt::BlockingQueuedConnection,
        Q_ARG(bool,true)
    );
    connect(
        element,
        SIGNAL(invoke(Invoke*)),
        this,
        SIGNAL(invoke(Invoke*))
    );
    connect(
        element,
        SIGNAL(insertAfterChildIndex(int,Node*)),
        this,
        SLOT(insertAfterChildIndexHandler(int,Node*))
    );
    connect(
        element,
        SIGNAL(appendChild(Node*)),
        this,
        SLOT(appendChildHandler(Node*))
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
        SIGNAL(renderSubtree(Node*)),
        this,
        SLOT(renderSubtreeHandler(Node*))
    );
    return component;
}

/*---------------------------------------------------------------------------*/

Window* Manager::renderWindow(Node *node, Element *parent) {
    Window* window = new Window(node, &engine, parent);
    connect(
        window,
        SIGNAL(closed()),
        this,
        SIGNAL(closed())
    );
    return window;
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

void Manager::renderSubtreeHandler(Node *child) {
    qDebug() << "Manager renderSubtreeHanler";
    Component* component = qobject_cast<Component*>(QObject::sender());
    QLinkedList<Element*> tree;
    tree.append(renderElementTree(child,component));
    component->receiveSubtree(tree);
    DiffCounter::instance()->decrementCounter();
}

/*---------------------------------------------------------------------------*/

void Manager::insertAfterChildIndexHandler(int index, Node *child) {
    qDebug() << "Manager insertAfterChildIndexHandler";
    Element* sender = qobject_cast<Element*>(QObject::sender());
    sender->childInsertAfterIndex(index, renderElementTree(child, sender));
    DiffCounter::instance()->decrementCounter();
}

/*---------------------------------------------------------------------------*/

void Manager::appendChildHandler(Node *child) {
    qDebug() << "Manager appendChildHandler";
    Element* sender = qobject_cast<Element*>(QObject::sender());
    sender->childAppend(renderElementTree(child, sender));
    DiffCounter::instance()->decrementCounter();
}

/*---------------------------------------------------------------------------*/

Manager::Manager(QObject *parent)
  : QObject(parent){
    qDebug() << "Manager ctor";
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
    }
}

/*---------------------------------------------------------------------------*/

void Manager::renderDialog(IDialog *dialog) {
    qDebug() << "Maganer renderDialog";
    dialog->show();
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
