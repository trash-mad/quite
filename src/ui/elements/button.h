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
  public:
    Button(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Button();
    virtual void invoke(
        QString type,
        QVariant p1,
        QVariant p2,
        QVariant p3,
        QVariant p4
    );
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // BUTTON_H
