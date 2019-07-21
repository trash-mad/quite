#ifndef COMPONENTNODE_H
#define COMPONENTNODE_H

#include <QThread>
#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QQmlEngine>
#include <QLinkedList>

#include "src/ui/base/node.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class ComponentNode : public Node {
  Q_OBJECT
  private:
    QMap<QString, QJSValue> state;
    QJSValue instance;
    QJSValue render;
  public:
    ComponentNode(
        QJSEngine* eval,
        QJSValue instance,
        QJSValue render
    );
    virtual ~ComponentNode();
    QJSValue getInstance() const;
  protected:
    void renderSubtree(QJSValue render);
  public slots:
    QJSValue setState(QJSValue state);
  signals:
    void childChanged(Node* node);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // COMPONENTNODE_H
