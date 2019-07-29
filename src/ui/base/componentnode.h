#ifndef COMPONENTNODE_H
#define COMPONENTNODE_H

#include <QVector>
#include <QtDebug>
#include <QObject>
#include <QJSEngine>

#include "src/ui/base/node.h"
#include "src/objects/nodestruct.h"

using namespace Quite::Objects;

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

/*
 * Класс подготавливает реализует функциональность Node и добавляет к ней
 * сборку последовательности для рендеринга
 */
class ComponentNode : public Node {
  Q_OBJECT
  private:
    QJSValue instance;
    QJSValue render;
  public:
    ComponentNode(QJSEngine* eval, QJSValue instance, QJSValue render);
    virtual ~ComponentNode() override;

  /*
   * Слот setState для начала обновления древа
   */
  public slots:
    void setState(QJSValue state);
    virtual void updateContext(
        QJSValue context,
        bool recursive = false
    ) override;

  /*
   * Методы для подготовки компонента к инкрементальному рендерингу
   */
  private:
    static QVector<NodeStruct> buildNodeTree(
        Node* root,
        QVector<NodeStruct>& result,
        bool newTree=false,
        NodeStruct* parent=nullptr,
        int lastIndex=0,
        int index=0
    );
    static QJSValue initialRender(
        QJSEngine* eval,
        QJSValue instance,
        QJSValue render
    );

  signals:
    void subtreeChanged(
        QVector<NodeStruct> newTree,
        QVector<NodeStruct> tree,
        Node* newChild
    );
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // COMPONENTNODE_H
