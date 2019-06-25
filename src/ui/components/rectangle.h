#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QtDebug>
#include <QObject>
#include <QQuickWindow>

#include "src/ui/base/component.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class Rectangle : public Component {
  public:
    Rectangle(Node* node, QQmlEngine* engine);
    virtual ~Rectangle();
    virtual void propsChanged(QMap<QString, QVariant> props);
    virtual void childChanged(QLinkedList<Component*> child);
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite

#endif // RECTANGLE_H
