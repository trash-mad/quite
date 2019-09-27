#ifndef ENTRY_H
#define ENTRY_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

class Entry: public Element {
  Q_OBJECT
  public:
    Entry(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Entry() override;
  public slots:
    virtual void onValueChanged(QVariant value) override;
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // ENTRY_H
