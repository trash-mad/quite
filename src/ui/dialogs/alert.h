#ifndef ALERT_H
#define ALERT_H

#include <QtDebug>
#include <QObject>
#include <QMessageBox>

#include "src/ui/base/dialog.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Dialogs {

/*****************************************************************************/

class Alert : public Dialog<QString>/*, public virtual IDialog*/ {
  private:
    QString text;
  public:
    explicit Alert(QString text);
    virtual ~Alert() override;
    virtual void show() override;
};

/*****************************************************************************/

} // namespace Dialogs
} // namespace Ui
} // namespace Quite

#endif // ALERT_H
