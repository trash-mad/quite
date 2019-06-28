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

/*---------------------------------------------------------------------------*/

void ElementWrapper::invoke(
    QString type,
    QVariant p1,
    QVariant p2,
    QVariant p3
){
    qDebug() << "ElementWrapper invoke";
    (void)(type);
    (void)(p1);
    (void)(p2);
    (void)(p3);
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
