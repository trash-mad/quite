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
#include "src/ui/base/componentnode.h"

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
    bool layoutUpdateScheduled=false;
  public:
    Element(QUrl uri, Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Element();

  /*
   * Слоты, привязываемые к контексту QML компонента
   * Они виртуальные - переопределяем в наследнике элемента
   */
  public slots:
    virtual void onClick();

  /*
   * Действия, выполняемые для синхронизации элемента и item. Доступны к
   * переопределению, но смысл сводится скорее к выполнению операции
   * перед стандартным действием (логгирование и тд)
   */
  public:
    virtual void childInsertAfter(Node* after, Element* child);
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
   *
   */
  private slots:
    void propsChangedHandler(QMap<QString, QVariant> commitProps, bool merge);
    void childInsertedAfterHandler(Node* after, Node* child);
    void childDeletedHandler(QObject* child);
    void childAppendedHandler(Node* child);
    void childDiffDeleteHandler();
    void diffDeleteEmit();

  /*
   * Метод для построения древа нод флекс-компоновки
   * переопределяется у окна для передачи актуального размера
   * в альтернативный конструктор
   */
  public:
    virtual FlexNode* buildFlexTree(bool fill=false);

  /*
   * Слот, перерисовывающий размеры дочернего древа. Публичный,
   * его также тригеррит окно при изменении размера
   * переопределяется у компонента, чтобы передать true в
   * параметры конструктора FlexNode
   */
  public slots:
    virtual void updateLayout(bool fill=false);

  /*
   * Сигналы для Manager, чтобы рендерить элементы
   */
  signals:
    void insertAfterChild(Node* after, Node* child);
    void appendChild(Node* child);
    void invoke(Invoke* method);

  /*
   * Сигнал для уведомления о изменении потомков
   */
  signals:
    void diffDelete();
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // ELEMENT_H
