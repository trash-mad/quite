#include "rectangle.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Rectangle::Rectangle(Node *node, QQmlEngine *engine, Element *parent)
  : Element(":/qml/Rectangle.qml", node, engine, parent) {
    qDebug() << "Rectangle ctor";
}

/*---------------------------------------------------------------------------*/

Rectangle::~Rectangle() {
    qDebug() << "Rectangle dtor";
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
