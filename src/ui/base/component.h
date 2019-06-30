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
    QMap<QString, QJSValue> props;
    Node* node;
  protected:
    QQuickItem* item;
    QQmlEngine* engine;
  public:
    Component(Node* node, QQmlEngine* engine, Component* parent);
    virtual ~Component();
    QLinkedList<Component*> getChild() const;
    QMap<QString, QJSValue> getProps() const;
    QQuickItem* getItem() const;
    Node* getNode() const;
    void silentPropUpdate(QString key, QJSValue value);
  protected:
    virtual void childChanged();
    virtual void propsChanged();
  public:
    virtual void invoke(
        QString type,
        QVariant p1,
        QVariant p2,
        QVariant p3
    ) = 0;
  public slots:
    void childChangedHandler(QLinkedList<Node*> child);
    void propsChangedHandler(QMap<QString, QJSValue> props);
  public slots:
    void receiveSubtree(QLinkedList<Component*> child);
  signals:
    void updateSubtree(Component* that, QLinkedList<Node*> child);
    void eval(QJSValue obj, QJSValueList args = QJSValueList());
    void propsChangedInvoked();
    void childChangedInvoked();
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // COMPONENT_H
