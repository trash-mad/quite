#include "invoker.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

Invoker::Invoker(QObject* parent)
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

void Invoker::setRoot(Component *root) {
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

Component *Invoker::findComponentByItem(Component *root, QQuickItem *item) {
    QQuickItem* current = root->getItem();
    if(current == item) {
        return root;
    } else {
        QLinkedList<Component*>::iterator i;
        QLinkedList<Component*> child = root->getChilds();
        for (i=child.begin(); i!=child.end();i++) {
            Component* result = findComponentByItem((*i), item);
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

void Invoker::invoke (
    QQuickItem* item,
    QString type,
    QVariant p1,
    QVariant p2,
    QVariant p3
) {
    qDebug() << "Invoker invoke";
    Component* component = findComponentByItem(root, item);
    if(component == nullptr) {
        qCritical() << "Invoker findComponentByItem nullptr";
    } else {
        component->invoke(type, p1, p2, p3);
    }
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
