#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class CheckBox: public Element {
  Q_OBJECT
  public:
    CheckBox(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~CheckBox() override;
  public slots:
    virtual void onCheck(bool enabled) override;
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // CHECKBOX_H
