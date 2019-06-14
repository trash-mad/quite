#ifndef WRAPPER_H
#define WRAPPER_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QJSValueIterator>

namespace Quite {
namespace Base {

/*****************************************************************************/

class Wrapper : public QObject {
  Q_OBJECT
  protected:
    QJSValue* object;
    static QObject* engine;
  private:
    explicit Wrapper(const QJSValue& original);
    virtual ~Wrapper();
    static Wrapper* wrapObject(QObject* engine, const QJSValue object);
  private slots:
    QJSValue call(QJSValueList args);
  public:
    static QJSValue fromQObject(
        QObject* engine,
        QObject *obj,
        QJSEngine* eval
    );
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // WRAPPER_H
