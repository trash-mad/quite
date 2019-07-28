#ifndef WINDOW_H
#define WINDOW_H

#include <QtDebug>
#include <QObject>
#include <QVariant>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class Window : public Element {
  Q_OBJECT
  public:
    Window(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Window() override;
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // WINDOW_H
