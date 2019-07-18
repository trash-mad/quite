#ifndef NODE_H
#define NODE_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QQmlEngine>
#include <QLinkedList>
#include <QReadWriteLock>
#include <QJSValueIterator>

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

enum NodeType {
    NeverType,
    ComponentType,
    ButtonType,
    WindowType,
    RectangleType
};

/*****************************************************************************/

class Node : public QObject {
  Q_OBJECT
  protected:
    NodeType type;
    QReadWriteLock locker;
    QLinkedList<Node*> child;
    QMap<QString, QJSValue> props;
  public:
    Node(
        QJSValue type,
        QJSValue props,
        QJSValue child
    );
    explicit Node(QObject* parent = nullptr);
    virtual ~Node();
    NodeType getType() const;
    QLinkedList<Node*> getChild() const;
    QMap<QString, QJSValue> getProps() const;
  public:
    static QMap<QString, QJSValue> getNodeParams(QJSValue props);
    static QLinkedList<Node*> castNodeList(QJSValue src);
    static bool tryCastNode(QJSValue src, Node*& dst);
    static NodeType getNodeType(QString type);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // NODE_H
