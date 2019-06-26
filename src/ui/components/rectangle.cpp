#include "rectangle.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

Rectangle::Rectangle(Node *node, QQmlEngine* engine, Component* parent)
  : Component(node, engine, parent) {
    qDebug() << "Rectangle ctor";
    QQmlComponent rect(engine, ":/qml/Rectangle.qml");
    item = qobject_cast<QQuickItem*>(rect.create());
}

/*---------------------------------------------------------------------------*/

Rectangle::~Rectangle() {
    qDebug() << "Rectangle dtor";
    delete item;
}

void Rectangle::invoke(QString type, QVariant p1, QVariant p2, QVariant p3) {
    (void)(type);
    (void)(p1);
    (void)(p2);
    (void)(p3);
    qCritical() << "Rectangle invoke not implemented";
}
/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
