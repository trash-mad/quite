#ifndef DIALOGEXTENSION_H
#define DIALOGEXTENSION_H

#include <QtDebug>
#include <QObject>
#include <QCoreApplication>

#include "src/base/extension.h"
#include "src/ui/dialogs/alert.h"
#include "src/ui/dialogs/prompt.h"
#include "src/events/renderdialog.h"

using namespace Quite::Base;
using namespace Quite::Events;
using namespace Quite::Ui::Dialogs;

namespace Quite {
namespace Extensions {

/*****************************************************************************/

class DialogExtension : public Extension {
  Q_OBJECT
  private:
    QJSEngine* eval;
  public:
    explicit DialogExtension(QObject* parent = nullptr);
    virtual ~DialogExtension();
    virtual void install(
        QJSValue global,
        QJSValue current,
        QJSEngine* eval
    );
  public slots:
    QJSValue alert(QJSValue msg);
    QJSValue prompt(QJSValue msg, QJSValue defaultValue);
};

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite

#endif // DIALOGEXTENSION_H
