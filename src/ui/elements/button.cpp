#include "button.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Button::Button(Node *node, QQmlEngine *engine, Element *parent)
  : Element(node, engine, parent) {
    qDebug() << "Button ctor";
    QQmlComponent rect(engine, ":/qml/Button.qml");
    item = qobject_cast<QQuickItem*>(rect.create());
}

/*---------------------------------------------------------------------------*/

Button::~Button() {
    qDebug() << "Button dtor";
}

/*---------------------------------------------------------------------------*/

void Button::invoke(
    QString type,
    QVariant p1,
    QVariant p2,
    QVariant p3,
    QVariant p4
) {
    if (type == "clicked") {
        QMap<QString, QJSValue> props = getProps();
        QMap<QString, QJSValue>::iterator i;
        for(i = props.begin(); i!= props.end(); i++) {
            if (i.key()=="onClicked") {
                emit eval(i.value());
            }
        }
    } else {
        Element::invoke(type, p1, p2, p3, p4);
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
