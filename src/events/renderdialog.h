#ifndef RENDERDIALOG_H
#define RENDERDIALOG_H

#include "src/base/event.h"
#include "src/ui/base/dialog.h"

using namespace Quite::Ui::Base;
using namespace Quite::Base;

namespace Quite {
namespace Events {

/*****************************************************************************/

class RenderDialog : public Event {
  private:
    IDialog* dialog;
  public:
    RenderDialog(IDialog* dialog);
    IDialog* getDialog() const;
    virtual ~RenderDialog() override;
    virtual EventResult process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    ) override;
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // RENDERDIALOG_H
