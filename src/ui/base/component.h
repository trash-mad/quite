#ifndef COMPONENT_H
#define COMPONENT_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QVariant>
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
    virtual QMap<QString,QVariant> propsChanged(QMap<QString,QJSValue> props);
    virtual void invoke(
        QString type,
        QVariant p1,
        QVariant p2,
        QVariant p3
    ) = 0;
  private slots:
    void childChangedHandler(QLinkedList<Node*> child);
  signals:
    void updateSubtree(Component* that, QLinkedList<Node*> child);
    void eval(QJSValue obj, QJSValueList args = QJSValueList());
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // COMPONENT_H
