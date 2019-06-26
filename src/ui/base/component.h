#ifndef COMPONENT_H
#define COMPONENT_H

#include <QtDebug>
#include <QObject>
#include <QQuickItem>
#include <QQmlEngine>

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
    QQmlEngine* engine;
  public:
    Component(Node* node, QQmlEngine* engine, Component* parent);
    virtual ~Component();
    QLinkedList<Component*> getChilds() const;
    QMap<QString, QVariant> getProps() const;
    QQuickItem* getItem() const;
  public:
    virtual void childChanged(QLinkedList<Component*> child);
    virtual void propsChanged(QMap<QString, QVariant> props);
  private slots:
    void childChangedHandler(QLinkedList<Node*> child);
    void propsChangedHandler(QMap<QString, QVariant> props);
  signals:
    void updateSubtree(Component* that, QLinkedList<Node*> child);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // COMPONENT_H
