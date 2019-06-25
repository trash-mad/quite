#ifndef COMPONENT_H
#define COMPONENT_H

#include <QtDebug>
#include <QObject>
#include <QQuickItem>

#include "src/ui/base/node.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class Component : public QObject {
  Q_OBJECT
  private:
    QLinkedList<Component*> child;
    QMap<QString, QVariant> props;
  protected:
    QQuickItem* item;
  public:
    Component(Node* node);
    virtual ~Component();
    QLinkedList<Component*> getChilds() const;
    QMap<QString, QVariant> getProps() const;
    QQuickItem* getItem() const;
  protected:
    virtual void propsChanged() = 0;
    virtual void childChanged(QLinkedList<Component*> child) = 0;
  private slots:
    void childChangedHandler(QLinkedList<Node*> child);
    void propsChangedHandler(QMap<QString, QVariant> props);
  signals:
    void updateSubtree(QLinkedList<Node*> child);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // COMPONENT_H
