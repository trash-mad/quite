#ifndef NODE_H
#define NODE_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QQmlEngine>
#include <QLinkedList>
#include <QReadWriteLock>
#include <QJSValueIterator>

#include "src/objects/invoke.h"

using namespace Quite::Objects;

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
    QLinkedList<Node*> child;
    QMap<QString, QJSValue> valueProps;
    QMap<QString, QVariant> variantProps;
    QJSValue executionContext = QJSValue();
  private:
    void gcInvoke();
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
    virtual QMap<QString, QVariant> getVariantProps();
    virtual void updateContext(QJSValue executionContext);
  public:
    static QMap<QString, QJSValue> getNodeParams(QJSValue props);
    static QLinkedList<Node*> castNodeList(QJSValue src);
    static bool tryCastNode(QJSValue src, Node*& dst);
    static NodeType getNodeType(QString type);
  protected:
    void generateVariantProps(QJSValue context);
  signals:
    void variantPropsChanged(QMap<QString, QVariant> props);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // NODE_H
