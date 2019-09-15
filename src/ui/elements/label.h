#ifndef LABEL_H
#define LABEL_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class Label: public Element {
  Q_OBJECT
  public:
    Label(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Label() override;
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // LABEL_H
