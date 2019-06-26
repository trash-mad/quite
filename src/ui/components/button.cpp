#include "button.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

Button::Button(Node* node, QQmlEngine* engine, Component* parent)
  : Component(node, engine, parent) {
    qDebug() << "Button ctor";
}

/*---------------------------------------------------------------------------*/

Button::~Button() {
    qDebug() << "Button dtor";
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
