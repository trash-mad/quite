#include "componentnode.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

ComponentNode::ComponentNode(
    QJSEngine* eval,
    QJSValue instance,
    QJSValue render
) : Node(
        QJSValue("Component"),
        instance.property("props"),
        ComponentNode::initialRender(eval, instance, render)
) {
    qDebug() << "ComponentNode ctor";
    instance.setProperty(
        "setState",
        eval->newQObject(this).property("setState")
    );
    this->instance=instance;
    this->render=render;

    this->getChild().first()->updateContext(instance);
}

/*---------------------------------------------------------------------------*/

ComponentNode::~ComponentNode() {
    qDebug() << "ComponentNode dtor";
}

/*---------------------------------------------------------------------------*/

void ComponentNode::setState(QJSValue state) {
    instance.setProperty("state", state);
    QJSValue root = render.callWithInstance(
        instance, {
            instance.property("props"),
            instance.property("state")
        }
    );
    Node* node = nullptr;
    if (tryCastNode(root, node)) {
        QVector<NodeStruct> newTree(node->getTotalChildCount());
        ComponentNode::buildNodeTree(node, newTree, true);
        QVector<NodeStruct> tree(getChild().first()->getTotalChildCount());
        ComponentNode::buildNodeTree(getChild().first(), tree);
        node->updateContext(instance);
        emit subtreeChanged(
            newTree,
            tree,
            node
        );
    } else {
        qCritical() << "ComponentNode setState render is not Node*";
    }
}

/*---------------------------------------------------------------------------*/

void ComponentNode::updateContext(
    QJSValue context,
    bool recursive
) {
    Q_UNUSED(recursive);
    Node::updateContext(context, false);
    Node::updateChildContext(instance);
}

/*---------------------------------------------------------------------------*/

QVector<NodeStruct> ComponentNode::buildNodeTree(
    Node* root,
    QVector<NodeStruct>& result,
    bool newTree,
    NodeStruct* parent,
    int lastIndex,
    int index
) {
    result[lastIndex].childCount=root->getTotalChildCount();
    result[lastIndex].type=root->getType();
    result[lastIndex].key=root->getKey();
    result[lastIndex].newTree=newTree;
    result[lastIndex].parent=parent;
    result[lastIndex].index=index;
    result[lastIndex].node=root;

    int selfIndex=lastIndex;

    QLinkedList<Node*> child=root->getChild();
    QLinkedList<Node*>::iterator iter;
    int currentIndex=0;
    for (iter=child.begin();iter!=child.end();iter++) {
        lastIndex++;
        currentIndex++;
        buildNodeTree(
            (*iter),
            result,
            newTree,
            std::addressof(result[selfIndex]),
            lastIndex,
            currentIndex
        );
    }
    return result;
}

/*---------------------------------------------------------------------------*/

QJSValue ComponentNode::initialRender(
    QJSEngine* eval,
    QJSValue instance,
    QJSValue render
) {
    qDebug() << "ComponentNode initialRender";
    Node* node = nullptr;
    QJSValue result;
    if (!render.isCallable()) {
        qCritical() << "ComponentNode initialRender render is not callable";
    } else {
        QJSValue root = render.callWithInstance(
            instance, {
                instance.property("props"),
                instance.property("state")
            }
        );
        if (root.isError()) {
            qCritical() << "ComponentNode initialRender" << root.toString();
        } else if (!tryCastNode(root, node)) {
            qCritical()
                << "initialRender renderSubtree"
                << "render result is not Node*";
        } else {
            result = eval->newArray(1);
            result.setProperty(0, eval->newQObject(node));
        }
    }
    return result;
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
