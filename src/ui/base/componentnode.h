#ifndef COMPONENTNODE_H
#define COMPONENTNODE_H

#include <QVector>
#include <QtDebug>
#include <QObject>
#include <QJSEngine>

#include <sstream>
#include <vector>

#include "src/ui/base/node.h"
#include "3rdparty/dtl/dtl.hpp"
#include "src/objects/nodestruct.h"
#include "src/ui/rendersynchronizer.h"

using namespace Quite::Objects;
using namespace Quite::Ui;

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
   * Вызов метода дождется окончания рендеринга окна и предотвратит новый,
   * пока Element не отчитаются о применении изменений
   */
  private:
    void incrementResolveCounter(QString from);
    void resolveChanges();

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

  /*
   * Методы для сравнения двух древ
   */
  private:
    bool checkTree(QVector<NodeStruct>& tree);
    bool tryInsertAfterChild(
        std::vector<NodeStruct>& merged,
        NodeStruct child,
        int lastIndex
    );
    bool tryAppendChild(
        std::vector<NodeStruct>& merged,
        NodeStruct child,
        int lastIndex
    );

  /*
   * Метод для обработки diff или полного рендеринга
   */
  private:
    void subtreeChanged(
        QVector<NodeStruct> newTree,
        QVector<NodeStruct> tree,
        Node* newRoot
    );

  /*
   * Сигнал для полного рендеринга, если diff невозможен
   */
  signals:
    void renderSubtree(Node* child);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // COMPONENTNODE_H
