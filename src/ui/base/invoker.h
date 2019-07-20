#ifndef INVOKER_H
#define INVOKER_H

#include <QtDebug>
#include <QObject>
#include <QVariant>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQmlContext>

#include "src/ui/base/element.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class Invoker : public QObject {
  Q_OBJECT
  private:
    Element* root;
  public:
    explicit Invoker(QObject* parent = nullptr);
    virtual ~Invoker();
    void install(QQmlEngine* engine);
    void setRoot(Element* root);
  private:
    Element* findElementByItem(Element* root, QQuickItem* item);
  public slots:
    void invoke(
        QQuickItem* obj,
        QString type,
        QVariant p1 = QVariant(),
        QVariant p2 = QVariant(),
        QVariant p3 = QVariant(),
        QVariant p4 = QVariant()
    );
};

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // INVOKER_H
