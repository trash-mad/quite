#ifndef FACTORY_H
#define FACTORY_H

#include <QJSEngine>
#include <QJSValue>
#include <QObject>
#include <QtDebug>

namespace Quite {
namespace Base {

/*****************************************************************************/

class Factory : public QObject {
  Q_OBJECT
  private:
    QJSEngine* eval;
  public:
    Factory(QObject* parent, QJSEngine* eval);
    virtual ~Factory();
    QJSValue newQObject(QObject* object);
    QJSValue newArray(uint lenght);
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // FACTORY_H
