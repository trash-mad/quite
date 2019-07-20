#include "invoker.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Invoker::Invoker(QObject *parent)
  : QObject(parent) {
    qDebug() << "Invoker ctor";
}

/*---------------------------------------------------------------------------*/

Invoker::~Invoker() {
    qDebug() << "Invoker dtor";
}

/*---------------------------------------------------------------------------*/

void Invoker::install(QQmlEngine *engine) {
    qDebug() << "Invoker install";
    engine->rootContext()->setContextProperty("Quite", this);
}

/*---------------------------------------------------------------------------*/

void Invoker::setRoot(Element *root) {
    qDebug() << "Invoker setRoot";
    /*
     * TODO: Invoker::setRoot() может проводить инициализацию для быстой
     * навигации по древу объектов. Текущая реализация, основанная на
     * рекурсивной функции, имеет не постоянную сложность - увеличивается с
     * разрастанием древа компонентов. Мы можем генерировать хеш-таблицу
     * для моментальной адресации заранее.
     */
    this->root = root;
}

/*---------------------------------------------------------------------------*/

Element *Invoker::findElementByItem(Element *root, QQuickItem *item) {
    QQuickItem* current = root->getItem();
    if(current == item) {
        return root;
    } else {
        QLinkedList<Element*>::iterator i;
        QLinkedList<Element*> child = root->getChild();
        for (i=child.begin(); i!=child.end();i++) {
            Element* result = findElementByItem((*i), item);
            if(result!=nullptr) {
                return result;
            } else {
                continue;
            }
        }
        return nullptr;
    }
}

/*---------------------------------------------------------------------------*/

void Invoker::invoke(
    QQuickItem *obj,
    QString type,
    QVariant p1,
    QVariant p2,
    QVariant p3,
    QVariant p4
) {
    qDebug() << "Invoker invoke";
    Element* element = findElementByItem(root, obj);
    if(element == nullptr) {
        qCritical() << "Invoker findComponentByItem nullptr";
    } else {
        element->invoke(type, p1, p2, p3, p4);
    }
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
