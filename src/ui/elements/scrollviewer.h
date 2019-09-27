#ifndef SCROLLVIEWER_H
#define SCROLLVIEWER_H

#include <QtDebug>
#include <QObject>
#include <QQmlComponent>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class ScrollViewer: public Element {
  Q_OBJECT
  public:
    ScrollViewer(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~ScrollViewer();
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // SCROLLVIEWER_H
