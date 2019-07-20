#include "rectangle.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Rectangle::Rectangle(Node *node, QQmlEngine *engine, Element *parent)
  : Element(node, engine, parent) {
    qDebug() << "Rectangle ctor";
    QQmlComponent rect(engine, ":/qml/Rectangle.qml");
    item = qobject_cast<QQuickItem*>(rect.create());
}

/*---------------------------------------------------------------------------*/

Rectangle::~Rectangle() {
    qDebug() << "Rectangle dtor";
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
