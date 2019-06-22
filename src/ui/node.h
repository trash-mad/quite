#ifndef NODE_H
#define NODE_H

#include <QMap>
#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QVariant>
#include <QQuickItem>
#include <QQmlEngine>
#include <QLinkedList>
#include <QJSValueIterator>

namespace Quite {
namespace Ui {

/*****************************************************************************/

class Node : public QObject {
  Q_OBJECT
  protected:
    QQuickItem* node;
    QQmlEngine* engine;
    QLinkedList<Node*> children;
    QMap<QString, QVariant> currentProps;
  public:
    Node(QObject *parent, QQmlEngine* engine);
    virtual ~Node();
    QQuickItem* getNode();
  protected:
    virtual void appendChild(Node* child) = 0;
    virtual void removeChild(Node* child) = 0;
    virtual void insertBefore(Node* child, Node* beforeChild) = 0;
    virtual void commitUpdate(QMap<QString, QVariant> props) = 0;
  public slots:
    QJSValue appendChild(QJSValue child);
    QJSValue removeChild(QJSValue child);
    QJSValue insertBefore(QJSValue child, QJSValue beforeChild);
    QJSValue commitUpdate(QJSValue props);
  private:
    static bool tryCast(QJSValue src, Node*& dst);
};

/*****************************************************************************/

} // namespace Ui
} // namespace Quite

#endif // NODE_H
