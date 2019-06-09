#ifndef EXTENSION_H
#define EXTENSION_H

#include <QJSEngine>
#include <QJSValue>
#include <QObject>
#include <QtDebug>
#include <QList>

#include "base/engine.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

class Extension : public QObject {
  Q_OBJECT
  private:
    Engine* _engine;
  public:
    explicit Extension(Engine* engine = nullptr);
    virtual ~Extension();
    virtual void install(QJSValue global) = 0;
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // EXTENSION_H
