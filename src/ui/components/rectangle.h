#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QEvent>
#include <QtDebug>
#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>

#include "src/ui/node.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class Rectangle : public Node {
  public:
    Rectangle(QObject *parent, QQmlEngine* engine);
    virtual ~Rectangle();
  protected:
    virtual void appendChild(Node* child);
    virtual void removeChild(Node* child);
    virtual void insertBefore(Node* child, Node* beforeChild);
    virtual void commitUpdate(QMap<QString, QVariant> props);
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite

#endif // RECTANGLE_H
