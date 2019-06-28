#include "elementwrapper.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

ElementWrapper::ElementWrapper(
    Node* node,
    QQmlEngine* engine,
    Component* parent
) : Component(node, engine, parent) {
    qDebug() << "Element ctor";
    item = new QQuickItem();
}

/*---------------------------------------------------------------------------*/

ElementWrapper::~ElementWrapper() {
    qDebug() << "Element dtor";
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
