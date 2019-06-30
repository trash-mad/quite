#ifndef ELEMENT_H
#define ELEMENT_H

#include <QMap>
#include <QList>
#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QLinkedList>

#include "src/ui/base/node.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class Element : public Node {
  Q_OBJECT
  private:
    QMap<QString, QJSValue> state;
    QJSValue instance;
    QJSEngine* eval;
    QJSValue render;
    QJSValue props;
  public:
    Element(
        QJSEngine* eval,
        QJSValue instance,
        QJSValue props,
        QJSValue state,
        QJSValue render
    );
    virtual ~Element();
    QMap<QString, QJSValue> getState() const;
    QJSValue getInstance() const;
  private:
    static QJSValue renderSubtree(
        QJSValue props,
        QJSValue state,
        QJSValue render,
        QJSEngine* engine
    );
    static QLinkedList<Node*> renderSubtree(
        QJSValue props,
        QJSValue state,
        QJSValue render
    );
  public slots:
    QJSValue setState(QJSValue state);
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // ELEMENT_H
