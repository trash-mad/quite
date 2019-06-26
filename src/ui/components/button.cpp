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
    QMap<QString, QVariant> tmp;
    QMap<QString, QJSValue>::iterator i;
    for(i = props.begin(); i!= props.end(); i++) {
        QString name = i.key();
        QJSValue value = i.value();
        if (name == "onClicked") {
            clickHandler = value;
        } else {
            item->setProperty(name.toStdString().c_str(),value.toVariant());
            tmp.insert(name, value.toVariant());
        }
    }
    return tmp;
}

/*---------------------------------------------------------------------------*/

void Button::invoke(QString type, QVariant p1, QVariant p2, QVariant p3) {
    qDebug() << "Button invoke";
    (void)(p1);
    (void)(p2);
    (void)(p3);
    if (type == "clicked") {
        emit eval(clickHandler);
    } else {
        qCritical() << "Button invoke"<<type<<"not found";
    }
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
