#ifndef RENDERUI_H
#define RENDERUI_H

#include <QtDebug>
#include <QObject>

#include "src/base/event.h"
#include "src/ui/base/node.h"

using namespace Quite::Ui::Base;
using namespace Quite::Base;

namespace Quite {
namespace Events {

/*****************************************************************************/

class RenderUi : public Event {
  private:
    Node* root;
  public:
    RenderUi(Node* root);
    virtual ~RenderUi();
    Node* getRootNode() const;
    virtual EventResult process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // RENDERUI_H
