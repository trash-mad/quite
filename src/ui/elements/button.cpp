#include "button.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Button::Button(Node *node, QQmlEngine *engine, Element *parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Button.qml")),
        node,
        engine,
        parent
    ){
    qDebug() << "Button ctor";
    getItem()->setHeight(45);
    getItem()->setWidth(125);
}

/*---------------------------------------------------------------------------*/

Button::~Button() {
    qDebug() << "Button dtor";
}

/*---------------------------------------------------------------------------*/

void Button::onElementClick() {
    QMap<QString, QVariant> props = getProps();
    Invoke* obj = nullptr;
    if (!props.contains("onClick")) {
        return;
    } else {
        QVariant callBack = props["onClick"];
        if (Invoke::tryCast(callBack, obj)) {
            qDebug() << "Button onClick";
            emit invoke(obj);
        } else {
            qCritical() << "Button onClick not callable";
        }
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
