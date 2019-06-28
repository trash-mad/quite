#ifndef QUITEEXTENSION_H
#define QUITEEXTENSION_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QQmlEngine>

#include "src/events/throwerror.h"
#include "src/ui/base/element.h"
#include "src/events/renderui.h"
#include "src/base/extension.h"
#include "src/events/await.h"
#include "src/ui/base/node.h"

using namespace Quite::Ui::Base;
using namespace Quite::Events;
using namespace Quite::Base;

namespace Quite {
namespace Extensions {

/*****************************************************************************/

class QuiteExtension : public Extension {
  Q_OBJECT
  private:
    Factory* factory;
  public:
    explicit QuiteExtension(QObject* parent = nullptr);
    virtual ~QuiteExtension();
    virtual void install(
        QJSValue global,
        QJSValue current,
        Factory* factory
    );
  private:
    QJSValue createElementInternal(
        QJSValue type,
        QJSValue props,
        QJSValue child
    );
  public slots:
    QJSValue render(QJSValue root);
    QJSValue createElement(
        QJSValue type,
        QJSValue props,
        QJSValue child1 = QJSValue(),
        QJSValue child2 = QJSValue(),
        QJSValue child3 = QJSValue()
    );
};

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite

#endif // QUITEEXTENSION_H
