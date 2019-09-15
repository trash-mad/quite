#ifndef BUTTON_H
#define BUTTON_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

/******************************************************************************/

class Button : public Element {
  Q_OBJECT
  public:
    Button(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Button() override;
  /*
   * Слот привязывается к контесту выполнения QML компонента в Element
   */
  public slots:
    virtual void onElementClick() override;
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // BUTTON_H
