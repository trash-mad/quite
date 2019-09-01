#ifndef PROMPT_H
#define PROMPT_H

#include <QtDebug>
#include <QObject>
#include <QInputDialog>

#include "src/ui/base/dialog.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Dialogs {

/*****************************************************************************/

class Prompt : public Dialog<QString> {
  private:
    QString message;
    QString defaultValue;
  public:
    Prompt(QString message, QString defaultValue);
    virtual ~Prompt() override;
    virtual void show() override;
};

/*****************************************************************************/

} // namespace Dialogs
} // namespace Ui
} // namespace Quite

#endif // PROMPT_H
