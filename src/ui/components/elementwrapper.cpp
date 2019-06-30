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
    Element* element = qobject_cast<Element*>(getNode());
    if (element==nullptr) {
        qCritical() << "ElementWrapper getNode() not Element";
    } else {
        this->instance = element->getInstance();
    }
    startChildChangeMonitor(this);
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

/*---------------------------------------------------------------------------*/

void ElementWrapper::startChildChangeMonitor(Component* root) {
    qDebug() << "ElementWrapper startChildChangeMonitor";
    QLinkedList<Component*> child = root->getChild();
    if (child.isEmpty()) {
        connect(
            root,
            SIGNAL(childChangedInvoked()),
            this,
            SLOT(startChildChangeMonitor())
        );
        connect(
            root,
            SIGNAL(propsChangedInvoked()),
            this,
            SLOT(bindComponentChildProps())
        );
        bindComponentChildProps(root);
    } else {
        QLinkedList<Component*>::iterator i;
        for (i=child.begin();i!=child.end();i++) {
            Component* current = (*i);
            startChildChangeMonitor(current);
        }
    }
}

/*---------------------------------------------------------------------------*/

void ElementWrapper::startChildChangeMonitor() {
    Component* root = qobject_cast<Component*>(QObject::sender());
    startChildChangeMonitor(root);
}

/*---------------------------------------------------------------------------*/

void ElementWrapper::bindComponentChildProps() {
    Component* component = qobject_cast<Component*>(QObject::sender());
    bindComponentChildProps(component);
}

/*---------------------------------------------------------------------------*/

void ElementWrapper::bindComponentChildProps(Component* component) {
    qDebug() << "ElementWrapper bindComponentChildProps";
    QMap<QString, QJSValue> props = component->getProps();
    NodeType type = component->getNode()->getType();
    if (type!=NodeType::ElementType) {
        QMap<QString, QJSValue>::iterator i;
        for(i = props.begin(); i!= props.end(); i++) {
            if (i.value().isCallable()) {
                BindMonitor* monitor = new BindMonitor(i.value(),instance);
                emit bindMethod(monitor);
                while(!monitor->isStarted()) {
                    QCoreApplication::processEvents();
                }
                QJSValue binded = monitor->getResult();
                component->silentPropUpdate(i.key(), binded);
            }
        }
    } else {
        return;
    }
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
