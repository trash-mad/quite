#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtDebug>
#include <QObject>
#include <QVariant>
#include <QQuickItem>
#include <QQmlEngine>

#include "src/ui/base/node.h"
#include "src/base/event.h"

using namespace Quite::Base;

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class Element : public QObject {
  Q_OBJECT
  protected:
    QLinkedList<Element*> child;
    QMap<QString, QVariant> props;
    Node* node;
  protected:
    QQuickItem* item;
    QQmlEngine* engine;
  public:
    Element(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Element();
    QLinkedList<Element*> getChild() const;
    QMap<QString, QVariant> getProps() const;
    QQuickItem* getItem() const;
    Node* getNode() const;
    virtual void invoke(
        QString type,
        QVariant p1,
        QVariant p2,
        QVariant p3,
        QVariant p4
    );
  private slots:
    void receiveProps(QMap<QString, QVariant> props);
  public slots:
    void receiveSubtree(QLinkedList<Element*> child);
  public:
    virtual void propsChanged();
    virtual void childChanged();
  signals:
    void eval(Event* e);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // ELEMENT_H
