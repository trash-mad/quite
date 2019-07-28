#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtDebug>
#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQmlContext>
#include <QQuickWindow>

#include "node.h"
#include "src/objects/invoke.h"

using namespace Quite::Objects;

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
  public:
    Element(QString compUri, Node* node, QQmlEngine* engine, Element* parent);
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
  protected:
    QMap<QString, QVariant> getProps() const;
    QLinkedList<Element*> getChild() const;
    virtual QQuickItem* getItem() const;
    NodeType getType() const;
    Node* getNode() const;

  /*
   * Получение элементов, собранных из нод
   */
  public:
    void receiveSubtree(QLinkedList<Element*> child);

  /*
   * Обработчики сигналов ноды
   */
  private slots:
    void propsChangedHandler(QMap<QString, QVariant> commitProps);
    void childInsertedAfterHandler(Node* after, Node* child);
    void childDeletedHandler(QObject* child);
    void childAppendedHandler(Node* child);

  /*
   * Сигналы для Manager, чтобы рендерить элементы
   */
  signals:
    void insertAfterChild(Node* after, Node* child);
    void appendChild(Node* child);
    void invoke(Invoke* method);
    void windowClosed();
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // ELEMENT_H
