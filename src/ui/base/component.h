#ifndef COMPONENT_H
#define COMPONENT_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/node.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class Component : public QObject {
  Q_OBJECT
  private:
    Node* node;
  public:
    explicit Component(Component* parent);
    virtual ~Component();
  private slots:
    void childChangedHandler(QLinkedList<Node*> child);
    void propsChangedHandler(QMap<QString, QVariant> props);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // COMPONENT_H
