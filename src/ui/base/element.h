#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QQuickItem>
#include <QQmlEngine>

#include "src/ui/base/node.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class Element : public QObject {
  Q_OBJECT
  protected:
    QLinkedList<Element*> child;
    QMap<QString, QJSValue> props;
    Node* node;
  protected:
    QQuickItem* item;
    QQmlEngine* engine;
  public:
    Element(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Element();
    QLinkedList<Element*> getChild() const;
    QMap<QString, QJSValue> getProps() const;
    QQuickItem* getItem() const;
    Node* getNode() const;
    virtual void invoke(
        QString type,
        QVariant p1,
        QVariant p2,
        QVariant p3,
        QVariant p4
    );
    void updateProps(QMap<QString, QJSValue> props);
    void updateProp(QString key, QJSValue value);
  public slots:
    void receiveSubtree(QLinkedList<Element*> child);
  protected:
    virtual void propsChanged();
    virtual void childChanged();
  signals:
    void eval(QJSValue obj, QJSValueList args = QJSValueList());
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // ELEMENT_H
