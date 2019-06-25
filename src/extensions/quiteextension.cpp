#include "quiteextension.h"

namespace Quite {
namespace Extensions {

/*****************************************************************************/

QuiteExtension::QuiteExtension(QObject* parent)
  : Extension(parent) {
    qDebug() << "QuiteExtension ctor";
}

/*---------------------------------------------------------------------------*/

QuiteExtension::~QuiteExtension() {
    qDebug() << "QuiteExtension dtor";
    factory->deleteLater();
}

/*---------------------------------------------------------------------------*/

void QuiteExtension::install(
    QJSValue global,
    QJSValue current,
    Factory* factory
) {
    qDebug() << "QuiteExtension install";
    global.setProperty("Quite", current);
    this->factory = factory;
}

/*---------------------------------------------------------------------------*/

QJSValue QuiteExtension::render(QJSValue root) {
    qDebug() << "QuiteExtension render";
    Node* node = nullptr;
    if(!Node::tryCastNode(root,node)){
        QCoreApplication::sendEvent(parent(), new Events::ThrowError(
            "render: invalid parameter rootNode"
        ));
    } else {
        qCritical() << "render not implemented";
    }
    return QJSValue();
}

/*---------------------------------------------------------------------------*/

QJSValue QuiteExtension::createElement(
    QJSValue type,
    QJSValue props,
    QJSValue child1,
    QJSValue child2,
    QJSValue child3
){
    qDebug() << "QuiteExtension createElement";
    QJSValue child;
    if(child1.isUndefined()) {
        child = QJSValue();
    } else if(child2.isUndefined()) {
        child = factory->newArray(1);
        child.setProperty(0, child1);
    } else if(child3.isUndefined()) {
        child = factory->newArray(2);
        child.setProperty(0, child1);
        child.setProperty(1, child2);
    } else {
        child = factory->newArray(3);
        child.setProperty(0, child1);
        child.setProperty(1, child2);
        child.setProperty(2, child3);
    }
    return createElementInternal(type, props, child);
}

/*---------------------------------------------------------------------------*/

QJSValue QuiteExtension::createElementInternal(
    QJSValue type,
    QJSValue props,
    QJSValue child
) {
    qDebug() << "QuiteExtension createElementInternal";
    Node* node  = new Node(type, props, child);
    return factory->newQObject(node);
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
