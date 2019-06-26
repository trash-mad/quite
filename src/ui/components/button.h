#ifndef BUTTON_H
#define BUTTON_H

#include <QtDebug>
#include <QObject>
#include <QVariant>

#include "src/ui/base/node.h"
#include "src/ui/base/component.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class Button : public Component {
  Q_OBJECT
  private:
    QJSValue clickHandler;
  public:
    Button(Node* node, QQmlEngine* engine, Component* parent);
    virtual ~Button();
    virtual QMap<QString, QVariant> propsChanged(QMap<QString, QJSValue> props);
    virtual void invoke(QString type, QVariant p1, QVariant p2, QVariant p3);
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite

#endif // BUTTON_H
