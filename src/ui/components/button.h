#ifndef BUTTON_H
#define BUTTON_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/node.h"
#include "src/ui/base/component.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class Button : public Component {
  Q_OBJECT
  public:
    Button(Node* node, QQmlEngine* engine, Component* parent);
    virtual ~Button();
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite

#endif // BUTTON_H
