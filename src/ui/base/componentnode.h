#ifndef COMPONENTNODE_H
#define COMPONENTNODE_H

#include <QTimer>
#include <QVector>
#include <QtDebug>
#include <QObject>
#include <QJSEngine>

#include <sstream>
#include <vector>

#include "src/ui/base/node.h"
#include "3rdparty/dtl/dtl.hpp"
#include "src/objects/nodestruct.h"
#include "src/ui/base/diffcounter.h"

using namespace Quite::Objects;
using namespace Quite::Ui::Base;

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
    QTimer* scheduleTimer;
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
        int& itemIndex,
        QVector<NodeStruct>& result,
        bool newTree=false,
        NodeStruct* parent=nullptr
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
    int countTotalChild(Node* root);
    bool checkTree(QVector<NodeStruct>& tree);
    void processDiffChild(
        std::vector<NodeStruct> &merged,
        NodeStruct item,
        int index
    );
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
