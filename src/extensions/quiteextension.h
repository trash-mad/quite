#ifndef QUITEEXTENSION_H
#define QUITEEXTENSION_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QQmlEngine>

#include "ui/components/window.h"
#include "events/throwerror.h"
#include "base/extension.h"
#include "ui/node.h"

using namespace Quite::Ui::Components;
using namespace Quite::Events;
using namespace Quite::Base;
using namespace Quite::Ui;

namespace Quite {
namespace Extensions {

/*****************************************************************************/

class QuiteExtension : public Extension {
  Q_OBJECT
  private:
    QQmlEngine* engine;
    Factory* factory;
  public:
    explicit QuiteExtension(QObject* parent = nullptr);
    virtual ~QuiteExtension();
    virtual void install(
        QJSValue global,
        QJSValue current,
        Factory* factory
    );
  public slots:
    QJSValue render(QJSValue windowComponent);
    QJSValue createComponent(QJSValue name);
};

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite

#endif // QUITEEXTENSION_H
