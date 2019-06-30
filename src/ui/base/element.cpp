#include "element.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Element::Element(
    QJSEngine* eval,
    QJSValue instance,
    QJSValue props,
    QJSValue state,
    QJSValue render
) : Node(QJSValue("Element"), props, renderSubtree(render, instance, eval)) {
    qDebug() << "Element ctor";
    this->state = getNodeParams(state);
    this->instance = instance;
    this->render = render;
    this->props = props;
    this->eval = eval;

    instance.prototype().setProperty(
        "setState",
        eval->newQObject(this).property("setState")
    );
}

/*---------------------------------------------------------------------------*/

Element::~Element() {
    qDebug() << "Element dtor";
}

/*---------------------------------------------------------------------------*/

QMap<QString, QJSValue> Element::getState() const {
    return state;
}

/*---------------------------------------------------------------------------*/

QJSValue Element::getInstance() const {
    return instance;
}

/*---------------------------------------------------------------------------*/

QJSValue Element::renderSubtree(
    QJSValue render,
    QJSValue instance,
    QJSEngine *eval
) {
    qDebug() << "Element renderSubtree";
    QJSValue result = eval->newArray(1);
    QJSValue child = eval->newQObject(
        renderSubtree(render,instance).first()
    );
    result.setProperty(0, child);
    return result;
}

/*---------------------------------------------------------------------------*/

QLinkedList<Node*> Element::renderSubtree(
    QJSValue render,
    QJSValue instance
) {
    QLinkedList<Node*> result;
    if (!render.isCallable()) {
        qCritical() << "Element renderSubtree render is not callable";
    } else {
        QJSValue root = render.callWithInstance(
            instance,
            {instance.property("props"), instance.property("state")}
        );
        Node* node = nullptr;
        if (root.isError()) {
            qCritical() << "Element renderSubree" << root.toString();
        } else if (!tryCastNode(root, node)) {
            qCritical() << "Element renderSubtree render result is not Node*";
        } else {
            result.append(node);
        }
    }
    return result;
}

/*---------------------------------------------------------------------------*/

QJSValue Element::setState(QJSValue state) {
    qDebug() << "Element setState";
    this->state = getNodeParams(state);
    instance.setProperty("state", state);
    commitChild(renderSubtree(render, instance, eval));
    return QJSValue();
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
