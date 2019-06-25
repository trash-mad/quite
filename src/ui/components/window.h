#ifndef WINDOW_H
#define WINDOW_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/component.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class Window : public Component{
  Q_OBJECT
  public:
    Window(Node* node);
    virtual ~Window();
    virtual void propsChanged(QMap<QString, QVariant> props);
    virtual void childChanged(QLinkedList<Component*> child);
    void show();
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite

#endif // WINDOW_H
