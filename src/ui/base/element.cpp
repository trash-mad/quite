#include "element.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Element::Element(
    Factory* factory,
    QJSValue props,
    QJSValue state,
    QJSValue render
) : Node(QJSValue("Element"), props, renderSubtree(props, state, render, factory)) {
    qDebug() << "Element ctor";
    this->render = render;
    this->props = props;
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

QJSValue Element::renderSubtree(
    QJSValue props,
    QJSValue state,
    QJSValue render,
    Factory *factory) {
    qDebug() << "Node renderSubtree";
    QJSValue result = factory->newArray(1);
    QJSValue child = factory->newQObject(renderSubtree(props,state,render));
    result.setProperty(0, child);
    return result;
}

/*---------------------------------------------------------------------------*/

Node* Element::renderSubtree(
    QJSValue props,
    QJSValue state,
    QJSValue render) {
    Node* result = nullptr;
    if (!render.isCallable()) {
        qCritical() << "Node renderSubtree render is not callable";
    } else {
        QJSValue root = render.call({props, state});
        if (!tryCastNode(root, result)) {
            qCritical() << "Node renderSubtree render result is not Node*";
        } else {
            return result;
        }
    }
    return result;
}

/*---------------------------------------------------------------------------*/

QJSValue Element::setState(QJSValue state) {
    this->state = getNodeParams(state);
    emit childChanged(
        QLinkedList<Node*>() << renderSubtree(props, state, render)
    );
    return QJSValue();
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
