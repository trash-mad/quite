#ifndef ELEMENT_H
#define ELEMENT_H

#include <QMap>
#include <QList>
#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QLinkedList>

#include "src/ui/base/node.h"
#include "src/base/factory.h"

using namespace Quite::Base;

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class Element : public Node {
  Q_OBJECT
  private:
    QMap<QString, QJSValue> state;
    QJSValue render;
    QJSValue props;
  public:
    Element(
        Factory* factory,
        QJSValue props = QJSValue(),
        QJSValue state = QJSValue(),
        QJSValue render = QJSValue()
    );
    virtual ~Element();
    QMap<QString, QJSValue> getState() const;
  private:
    static QJSValue renderSubtree(
        QJSValue props,
        QJSValue state,
        QJSValue render,
        Factory* factory
    );
    static Node* renderSubtree(
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
