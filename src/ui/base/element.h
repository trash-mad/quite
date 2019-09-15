#ifndef ELEMENT_H
#define ELEMENT_H

#include <QUrl>
#include <QtDebug>
#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQmlContext>
#include <QQuickWindow>
#include <QStringLiteral>

#include "src/ui/base/node.h"
#include "src/objects/invoke.h"
#include "src/objects/flexnode.h"
#include "src/ui/base/diffcounter.h"

using namespace Quite::Objects;
using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class Element : public QObject {
  Q_OBJECT
  private:
    QMap<QString, QVariant> props;
    QLinkedList<Element*> child;
    QQmlContext* context;
    NodeType type;
    Node* node;
  private:
    QQuickItem* item;
  protected:
    FlexNode* layout=nullptr;
  private:
    bool layoutUpdateStarted=false;
    bool layoutUpdateScheduled=false;
  public:
    Element(QUrl uri, Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Element();

  /*
   * Слоты, привязываемые к контексту QML компонента
   * Они виртуальные - переопределяем в наследнике элемента
   */
  public slots:
    virtual void onElementClick();
    virtual void onElementCheck(bool enabled);
    virtual void onElementValueChanged(QVariant value);

  /*
   * Действия, выполняемые для синхронизации элемента и item. Доступны к
   * переопределению, но смысл сводится скорее к выполнению операции
   * перед стандартным действием (логгирование и тд)
   */
  public:
    virtual void childInsertAfterIndex(int index, Element* child);
    virtual void childAppend(Element* child);
  protected:
    virtual void childDeleted(Element* child);
    virtual void childChanged();
    virtual void propsChanged();

  /*
   * Геттеры, сеттеры
   */
  public:
    QMap<QString, QVariant> getProps() const;
    QLinkedList<Element*> getChild() const;
    virtual QQuickItem* getItem() const;
    FlexNode* getLayout() const;
    NodeType getType() const;
    Node* getNode() const;

  /*
   * Получение элементов, собранных из нод
   */
  public:
    virtual void receiveSubtree(QLinkedList<Element*> child);

  /*
   * Обработчики сигналов ноды. Возможно, в связи с парралельной работой QML и JS
   * данные методы должны создать критерый для ожидания (bool), который
   * будет мониторится через геттер в наследнике Component
   * и реализовывать ожидание завершения перед новым рендерингом
   */
  private slots:
    void propsChangedHandler(QMap<QString, QVariant> commitProps, bool merge);
    void childInsertedAfterIndexHandler(int index, Node* child);
    void childDeletedHandler(QObject* child);
    void childAppendedHandler(Node* child);
    void childDiffDeleteHandler();
    void diffDeleteEmit();

  /*
   * Метод для построения древа нод флекс-компоновки
   *  - переопределяется у окна для передачи актуального размера
   * в альтернативный конструктор
   *  - переопределяется у компонента с передачей true в
   * конструктор по умолчанию
   */
  public:
    virtual FlexNode* buildFlexTree(bool fill=false);

  /*
   * Слот, перерисовывающий размеры дочернего древа. Реализует ожидание
   * применения изменений и вызов updateLayoutNow()
   */
  public slots:
    void updateLayout();

  /*
   * Вызывается окном и позволяет элементу начать считать diff flexbox
   */
  public:
    void startLayoutUpdate();

  /*
   * Подразумевается, что updateLayout() может пропустить перерисовку,
   * так как не все изменения diff древа применены. Этот метод
   * гарантированно выполнит перерасчет.
   *
   * Переопределяется у окна для инициализации просчета дерева
   */
  protected:
    virtual void updateLayoutNow();

  /*
   * Сигналы для Manager, чтобы рендерить элементы
   */
  signals:
    void insertAfterChildIndex(int index, Node* child);
    void appendChild(Node* child);
    void invoke(Invoke* method);

  /*
   * Сигнал для уведомления о изменении свойств/потомков
   */
  signals:
    void diffDelete();
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // ELEMENT_H
