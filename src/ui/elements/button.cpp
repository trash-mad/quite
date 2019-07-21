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
        QMap<QString, QVariant> props = getProps();
        QMap<QString, QVariant>::iterator i;
        for(i = props.begin(); i!= props.end(); i++) {
            if (i.key()=="onClicked") {
                Invoke* invoke = nullptr;
                if (Invoke::tryCast(i.value(), invoke)) {
                    qDebug() << "emit";
                    emit eval(invoke->createEval({}));
                } else {
                    qCritical() << "Button onClicked is not callable";
                }
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
