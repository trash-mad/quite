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

void Button::invoke(QString type, QVariant p1, QVariant p2, QVariant p3) {
    qDebug() << "Button invoke";
    (void)(p1);
    (void)(p2);
    (void)(p3);
    if (type == "clicked") {
        QMap<QString, QJSValue> props = getProps();
        QMap<QString, QJSValue>::iterator i;
        for(i = props.begin(); i!= props.end(); i++) {
            if (i.key()=="onClicked") {
                emit eval(i.value());
            }
        }
    } else {
        qCritical() << "Button invoke"<<type<<"not found";
    }
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
