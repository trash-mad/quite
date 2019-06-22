#ifndef QUITEEXTENSION_H
#define QUITEEXTENSION_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QQmlEngine>

#include "src/ui/components/rectangle.h"
#include "src/monitors/windowmonitor.h"
#include "src/ui/components/window.h"
#include "src/events/throwerror.h"
#include "src/base/extension.h"
#include "src/events/await.h"
#include "src/ui/node.h"

using namespace Quite::Ui::Components;
using namespace Quite::Monitors;
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
    QJSValue createElement(
        QJSValue name,
        QJSValue props,
        QJSValue child = QJSValue()
    );
  private:
    static bool tryCastWindow(QJSValue src, Window*& dst);
};

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite

#endif // QUITEEXTENSION_H
