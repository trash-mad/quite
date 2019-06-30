#ifndef NODE_H
#define NODE_H

#include <QMap>
#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QVariant>
#include <QLinkedList>
#include <QJSValueIterator>

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

enum NodeType {
    NeverType,
    ElementType,
    ButtonType,
    WindowType,
    RectangleType
};

/*****************************************************************************/

class Node : public QObject {
  Q_OBJECT
  private:
    NodeType type;
    QLinkedList<Node*> child;
    QMap<QString, QJSValue> props;
  public:
    explicit Node(
        QJSValue type = QJSValue(),
        QJSValue props = QJSValue(),
        QJSValue child = QJSValue()
    );
    virtual ~Node();
    NodeType getType() const;
    QLinkedList<Node*> getChild() const;
    QMap<QString, QJSValue> getProps() const;
  public:
    static QMap<QString, QJSValue> getNodeParams(QJSValue props);
    static QLinkedList<Node*> castNodeList(QJSValue src);
    static bool tryCastNode(QJSValue src, Node*& dst);
    static NodeType getNodeType(QString type);
  public slots:
    QJSValue commitChild(QJSValue child);
    QJSValue commitProps(QJSValue props);
  signals:
    void childChanged(QLinkedList<Node*> child);
    void propsChanged(QMap<QString, QJSValue> props);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // NODE_H
