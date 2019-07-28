#include "button.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Button::Button(Node *node, QQmlEngine *engine, Element *parent)
  : Element(":/qml/Button.qml", node, engine, parent) {
    qDebug() << "Button ctor";
}

/*---------------------------------------------------------------------------*/

Button::~Button() {
    qDebug() << "Button dtor";
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
