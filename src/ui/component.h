#ifndef COMPONENT_H
#define COMPONENT_H

#include <QtDebug>
#include <QObject>
#include <QVector>

#include "src/ui/base/componentnode.h"
#include "src/objects/nodestruct.h"
#include "src/ui/base/element.h"
#include "3rdparty/dtl/dtl.hpp"

using namespace Quite::Ui::Base;
using namespace Quite::Objects;

namespace Quite {
namespace Ui {

/*****************************************************************************/

class Component : public Element {
  Q_OBJECT
  private:
    bool diffImposible=false;
  public:
    Component(ComponentNode* node, QQmlEngine* engine, Element* parent);
    virtual ~Component() override;

  private slots:
    void renderSubtreeHandler(Node* child);

  signals:
    void renderSubtree(Node* child);
};

/*****************************************************************************/

} // namespace Ui
} // namespa Quite

#endif // COMPONENT_H
