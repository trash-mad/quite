#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class ComboBox: public Element {
  Q_OBJECT
  public:
    ComboBox(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~ComboBox() override;
  public slots:
    virtual void onElementSelectionChanged(int index) override;
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // COMBOBOX_H
