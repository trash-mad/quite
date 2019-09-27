#ifndef SLIDER_H
#define SLIDER_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class Slider: public Element {
  Q_OBJECT
  public:
    Slider(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Slider() override;
  public slots:
    virtual void onValueChanged(QVariant value) override;
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // SLIDER_H
