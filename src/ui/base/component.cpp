#include "component.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Component::Component(Component* parent)
  : QObject(parent) {
    qDebug() << "Component ctor";
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

void Component::childChangedHandler(QLinkedList<Node *> child) {
    (void)(child);
    qCritical() << "not implemented";
}

/*---------------------------------------------------------------------------*/

void Component::propsChangedHandler(QMap<QString, QVariant> props) {
    (void)(props);
    qCritical() << "not implemented";
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
