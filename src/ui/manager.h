#ifndef MANAGER_H
#define MANAGER_H

#include <QtDebug>
#include <QObject>

#include "src/base/event.h"

#include "src/ui/base/node.h"
#include "src/ui/base/element.h"
#include "src/ui/base/componentnode.h"

#include "src/ui/component.h"
#include "src/ui/elements/window.h"
#include "src/ui/elements/button.h"
#include "src/ui/elements/rectangle.h"

using namespace Quite::Base;
using namespace Quite::Ui::Base;
using namespace Quite::Ui::Elements;

namespace Quite {
namespace Ui {

/*****************************************************************************/

class Manager : public QObject {
  Q_OBJECT
  private:
    Window* rootElement = nullptr;
    QQmlEngine engine;
  public:
    explicit Manager(QObject* parent = nullptr);
    virtual ~Manager();
  public slots:
    void renderUi(Node* rootNode);
  private:
    Component* renderComponent(Node* node, Element* parent);
    Element* renderElement(Node* node, Element* parent = nullptr);
    Element* renderElementTree(Node* node, Element* parent = nullptr);
  private slots:
    void updateSubtree(Node* child, Component* that);
  signals:
    void closed();
    void eval(Event* e);
};

/*****************************************************************************/

} // namespace Ui
} // namespace Quite

#endif // MANAGER_H
