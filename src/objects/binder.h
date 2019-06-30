#ifndef BINDER_H
#define BINDER_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>

namespace Quite {
namespace Objects {

/*****************************************************************************/

class Binder : public QObject {
  Q_OBJECT
  private:
    QJSValue func;
    QJSValue instance;
  private:
    Binder(QJSValue func, QJSValue instance, QObject* parent = nullptr);
    virtual ~Binder();
  public:
    static QJSValue bind(QJSValue func, QJSValue instance, QJSEngine* eval);
  public slots:
    QJSValue call(
        QJSValue p1 = QJSValue(),
        QJSValue p2 = QJSValue(),
        QJSValue p3 = QJSValue(),
        QJSValue p4 = QJSValue(),
        QJSValue p5 = QJSValue()
    );
};

/*****************************************************************************/

} // namespace Objects
} // namespace Quite

#endif // BINDER_H
