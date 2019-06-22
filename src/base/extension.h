#ifndef EXTENSION_H
#define EXTENSION_H

#include <QJSEngine>
#include <QJSValue>
#include <QObject>
#include <QtDebug>
#include <QList>

#include "src/base/factory.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

class Extension : public QObject {
  Q_OBJECT
  public:
    explicit Extension(QObject* parent = nullptr);
    virtual ~Extension();
    virtual void install(
        QJSValue global,
        QJSValue current,
        Factory* factory
    ) = 0;
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // EXTENSION_H
