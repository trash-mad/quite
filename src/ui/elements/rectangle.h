#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QtDebug>
#include <QObject>
#include <QQmlComponent>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class Rectangle : public Element {
  public:
    Rectangle(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Rectangle();
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // RECTANGLE_H
