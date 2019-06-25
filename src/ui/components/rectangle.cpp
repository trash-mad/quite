#include "rectangle.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

Rectangle::Rectangle(Node *node, QQmlEngine* engine)
  : Component(node, engine) {
    qDebug() << "Rectangle ctor";
    QQmlComponent rect(engine, ":/qml/Rectangle.qml");
    item = qobject_cast<QQuickItem*>(rect.create());
}

/*---------------------------------------------------------------------------*/

Rectangle::~Rectangle() {
    qDebug() << "Rectangle dtor";
    delete item;
}

/*---------------------------------------------------------------------------*/

void Rectangle::propsChanged(QMap<QString, QVariant> props) {
    qDebug() << "Rectangle propsChanged";
    QMap<QString, QVariant>::iterator i;
    for(i = props.begin(); i!= props.end(); i++) {
        item->setProperty(i.key().toStdString().c_str(),i.value());
    }
}

/*---------------------------------------------------------------------------*/

void Rectangle::childChanged(QLinkedList<Component *> child) {
    qDebug() << "Rectangle childChanged";
    (void)(child);
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
