#include "button.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

Button::Button(Node* node, QQmlEngine* engine, Component* parent)
  : Component(node, engine, parent) {
    qDebug() << "Button ctor";
    QQmlComponent rect(engine, ":/qml/Button.qml");
    item = qobject_cast<QQuickItem*>(rect.create());
}

/*---------------------------------------------------------------------------*/

Button::~Button() {
    qDebug() << "Button dtor";
    delete item;
}

/*---------------------------------------------------------------------------*/

QMap<QString, QVariant> Button::propsChanged(QMap<QString, QJSValue> props) {
    qDebug() << "Button propsChanged";
    //todo
    return Component::propsChanged(props);
}

/*---------------------------------------------------------------------------*/

void Button::invoke(QString type, QVariant p1, QVariant p2, QVariant p3) {
    (void)(type);
    (void)(p1);
    (void)(p2);
    (void)(p3);
    qDebug() << "Button invoke";
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
