#ifndef ELEMENTWRAPPER_H
#define ELEMENTWRAPPER_H

#include <QtDebug>
#include <QObject>
#include <QQuickItem>

#include "src/ui/base/node.h"
#include "src/ui/base/component.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class ElementWrapper : public Component {
  Q_OBJECT
  public:
    ElementWrapper(Node* node, QQmlEngine* engine, Component* parent);
    virtual ~ElementWrapper();
    virtual void invoke(QString type, QVariant p1, QVariant p2, QVariant p3);
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite

#endif // ELEMENTWRAPPER_H
