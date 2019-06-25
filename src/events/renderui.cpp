#include "renderui.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

RenderUi::RenderUi(Node* root) {
    qDebug() << "RenderUi ctor";
    this->root = root;
}

/*---------------------------------------------------------------------------*/

RenderUi::~RenderUi() {
    qDebug() << "RenderUi dtor";
}

/*---------------------------------------------------------------------------*/

Node *RenderUi::getRootNode() const {
    return root;
}

/*---------------------------------------------------------------------------*/

EventResult RenderUi::process(
    QObject *engine,
    QJSEngine *eval,
    QThreadPool *pool
) {
    qDebug() << "RenderUi process";
    (void)(engine);
    (void)(pool);
    (void)(eval);
    return EventResult::EmitRenderUi;
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
