#ifndef WRAPPER_H
#define WRAPPER_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QMetaObject>
#include <QSharedPointer>

#include "base/object.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

class Wrapper : public QObject {
  Q_OBJECT
  private:
    QObject* _receiver;
    const char* _member;
  public:
    Wrapper(QObject *receiver, QString member);
    virtual ~Wrapper();
  public slots:
    void invoke(QJSValueList args);
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // WRAPPER_H
