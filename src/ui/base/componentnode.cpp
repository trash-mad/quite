#include "componentnode.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

ComponentNode::ComponentNode(
    QJSEngine *eval,
    QJSValue instance,
    QJSValue render
) {
    qDebug() << "ComponentNode ctor";
    this->valueProps = Node::getNodeParams(instance.property("props"));
    this->state = Node::getNodeParams(instance.property("state"));
    this->type = NodeType::ComponentType;
    this->instance = instance;
    this->render = render;

    generateVariantProps();

    instance.prototype().setProperty(
        "setState",
        eval->newQObject(this).property("setState")
    );

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    renderSubtree(this->render);
}

/*---------------------------------------------------------------------------*/

ComponentNode::~ComponentNode() {
    qDebug() << "ComponentNode dtor";
}

/*---------------------------------------------------------------------------*/

QJSValue ComponentNode::getInstance() const {
    return instance;
}

/*---------------------------------------------------------------------------*/

void ComponentNode::renderSubtree(QJSValue render) {
    qDebug() << "ComponentNode renderSubtree";
    Node* node = nullptr;
    if (!render.isCallable()) {
        qCritical() << "ComponentNode renderSubtree render is not callable";
    } else {
        QJSValue root = render.callWithInstance(
            instance, {
                instance.property("props"),
                instance.property("state")
            }
        );
        if (root.isError()) {
            qCritical() << "ComponentNode renderSubree" << root.toString();
        } else if (!tryCastNode(root, node)) {
            qCritical()
                << "ComponentNode renderSubtree"
                << "render result is not Node*";
        } else {
            if(!child.isEmpty()) {
                Node* child = this->child.first();
                child->deleteLater();
                this->child.clear();
            }
            child.append(node);
            updateContext(instance);
            emit childChanged(node);
        }
    }
}

/*---------------------------------------------------------------------------*/

QJSValue ComponentNode::setState(QJSValue state) {
    qDebug() << "ComponentNode setState" << QThread::currentThreadId();
    this->state = getNodeParams(state);
    instance.setProperty("state", state);
    renderSubtree(this->render);
    return QJSValue();
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
