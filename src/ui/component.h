#ifndef COMPONENT_H
#define COMPONENT_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>

#include "src/ui/base/componentnode.h"
#include "src/monitors/bindmonitor.h"
#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;
using namespace Quite::Monitors;

namespace Quite {
namespace Ui {

/*****************************************************************************/

class Component : public Element {
  Q_OBJECT
  private:
    QJSValue instance;
  public:
    Component(ComponentNode* node, QQmlEngine* engine, Element* parent);
    virtual ~Component();
  protected:
    virtual void childChanged() override;
  private:
    void bindChildElementCallbacks(Element* root);
  public slots:
    void receiveSubtree(Element* child);
  private slots:
    void requireSubtree(Node* child);
  signals:
    void updateSubtree(Node* child, Component* that);
    void bindMethod(BindMonitor* monitor);
};

/*****************************************************************************/

} // namespace Ui
} // namespace Quite

#endif // COMPONENT_H
