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
) : Node(QJSValue("Element"), props, renderSubtree(props, state, render, eval)) {
    qDebug() << "Element ctor";
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
    QJSValue props,
    QJSValue state,
    QJSValue render,
    QJSEngine *eval) {
    qDebug() << "Element renderSubtree";
    QJSValue result = eval->newArray(1);
    QJSValue child = eval->newQObject(
        renderSubtree(props,state,render).first()
    );
    result.setProperty(0, child);
    return result;
}

/*---------------------------------------------------------------------------*/

QLinkedList<Node*> Element::renderSubtree(
    QJSValue props,
    QJSValue state,
    QJSValue render) {
    QLinkedList<Node*> result;
    if (!render.isCallable()) {
        qCritical() << "Element renderSubtree render is not callable";
    } else {
        QJSValue root = render.call({props, state});
        Node* node = nullptr;
        if (!tryCastNode(root, node)) {
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
    commitChild(renderSubtree(props, state,render,eval));
    return QJSValue();
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
