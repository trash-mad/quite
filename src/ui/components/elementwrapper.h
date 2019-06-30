#ifndef ELEMENTWRAPPER_H
#define ELEMENTWRAPPER_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QQuickItem>

#include "src/ui/base/node.h"
#include "src/ui/base/element.h"
#include "src/ui/base/component.h"
#include "src/monitors/bindmonitor.h"

using namespace Quite::Ui::Base;
using namespace Quite::Monitors;

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class ElementWrapper : public Component {
  Q_OBJECT
  private:
    QJSValue instance;
  public:
    ElementWrapper(
        Node* node,
        QQmlEngine* engine,
        Component* parent
    );
    virtual ~ElementWrapper();
    virtual void invoke(QString type, QVariant p1, QVariant p2, QVariant p3);
  private:
    void startChildChangeMonitor(Component* root);
    void bindComponentChildProps(Component* component);
  private slots:
    void startChildChangeMonitor();
    void bindComponentChildProps();
  signals:
    void bindMethod(BindMonitor* monitor);
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite

#endif // ELEMENTWRAPPER_H
