#include "rectangle.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Rectangle::Rectangle(Node *node, QQmlEngine *engine, Element *parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Rectangle.qml")),
        node,
        engine,
        parent
    ) {
    qDebug() << "Rectangle ctor";
    getItem()->setHeight(50);
    getItem()->setWidth(50);
}

/*---------------------------------------------------------------------------*/

Rectangle::~Rectangle() {
    qDebug() << "Rectangle dtor";
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
