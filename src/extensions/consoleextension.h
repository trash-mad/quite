#ifndef CONSOLEEXTENSION_H
#define CONSOLEEXTENSION_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>

#include <iostream>

#include "base/extension.h"

using namespace Quite::Base;

namespace Quite {
namespace Extensions {

/*****************************************************************************/

class ConsoleExtension : public Extension {
  Q_OBJECT
  public:
    explicit ConsoleExtension(QObject* parent = nullptr);
    virtual ~ConsoleExtension();
    virtual void install(
        QJSValue global,
        QJSValue current,
        Factory* factory
    );
  public slots:
    QJSValue log(QJSValue msg);
};

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite

#endif // CONSOLEEXTENSION_H
