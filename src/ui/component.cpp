#include "component.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Component::Component(ComponentNode* node, QQmlEngine *engine, Element *parent)
  : Element(node, engine, parent) {
    qDebug() << "Component ctor";
    item = new QQuickItem();
    instance = node->getInstance();
    connect(
        node,
        SIGNAL(childChanged(Node*)),
        this,
        SLOT(requireSubtree(Node*))
    );
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

void Component::childChanged() {
    qDebug() << "Component childChanged";
    bindChildElementCallbacks(this);
    Element::childChanged();
}

/*---------------------------------------------------------------------------*/

void Component::bindChildElementCallbacks(Element* root) {
    QMap<QString, QJSValue> props = root->getProps();
    NodeType type = root->getNode()->getType();
    if (type!=NodeType::ComponentType) {
        QMap<QString, QJSValue>::iterator i;
        for(i = props.begin(); i!= props.end(); i++) {
            if (i.value().isCallable()) {
                BindMonitor* monitor = new BindMonitor(i.value(),instance);
                emit bindMethod(monitor);
                while(!monitor->isStarted()) {
                    /*
                     * TODO: требуется перерисовать диалог, не обрабатывая
                     * иные события
                     *
                     * методом научного тыка по кнопке с разной частотой,
                     * удалось поймать отладчиком наезд в этом месте
                     *
                     * QCoreApplication::processEvents(
                     *   QEventLoop::ProcessEventsFlag::DialogExec
                     * );
                     */
                    QThread::msleep(10);
                }
                QJSValue binded = monitor->getResult();
                root->updateProp(i.key(), binded);
            }
        }
    }
    QLinkedList<Element*> child = root->getChild();
    QLinkedList<Element*>::iterator i;
    for (i=child.begin();i!=child.end();i++) {
        Element* current = (*i);
        bindChildElementCallbacks(current);
    }
}

/*---------------------------------------------------------------------------*/

void Component::receiveSubtree(Element* child) {
    qDebug() << "Component receiveSubtree";
    this->child.append(child);
    childChanged();
}

/*---------------------------------------------------------------------------*/

void Component::requireSubtree(Node *child) {
    qDebug() << "Component emitUpdateSubtree";
    QLinkedList<Element*>::iterator i;
    for (i = this->child.begin(); i != this->child.end(); i++){
        Element* element = (*i);
        element->deleteLater();
    }
    this->child.erase(this->child.begin(), this->child.end());
    emit updateSubtree(child, this);
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
