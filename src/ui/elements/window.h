#ifndef WINDOW_H
#define WINDOW_H

#include <QtDebug>
#include <QObject>
#include <QVariant>

#include "src/ui/base/element.h"
#include "src/ui/flex/flexnode.h"
#include "src/ui/base/diffcounter.h"
#include "src/ui/components/windowcomponent.h"

using namespace Quite::Ui::Flex;
using namespace Quite::Ui::Base;
using namespace Quite::Ui::Components;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class Window : public Element {
  Q_OBJECT
  public:
    Window(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Window() override;
  private:
    FlexNode* buildFlexTree(Element* current);

  /*
   * Подписывается на сигнал обновления и выполняет первую рисовку
   */
  public:
    void startFlexLayout();

  /*
   * Слот для изменения компоновки флексбокс при обновлении дочерних
   * элементов
   */
  private slots:
    void updateFlexLayout();

  signals:
    void closed();
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // WINDOW_H
