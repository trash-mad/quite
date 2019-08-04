#ifndef MANAGER_H
#define MANAGER_H

#include <QtDebug>
#include <QObject>

#include "src/base/event.h"
#include "src/objects/invoke.h"

#include "src/ui/base/node.h"
#include "src/ui/base/element.h"
#include "src/ui/base/componentnode.h"

#include "src/ui/component.h"
#include "src/ui/elements/window.h"
#include "src/ui/elements/button.h"
#include "src/ui/elements/rectangle.h"

#include "src/ui/rendersynchronizer.h"

using namespace Quite::Ui;
using namespace Quite::Base;
using namespace Quite::Objects;
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
  /*
   * Слоты для рендеринга, запрашиваемого компонентом.
   */
  private slots:
    void renderSubtreeHandler(Node* child);
    void insertAfterChildHandler(Node* after, Node* child);
    void appendChildHandler(Node* child);

  signals:
    void closed();
    void invoke(Invoke* o);
};

/*****************************************************************************/

} // namespace Ui
} // namespace Quite

#endif // MANAGER_H
