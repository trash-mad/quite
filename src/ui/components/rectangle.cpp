#include "rectangle.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

Rectangle::Rectangle(QObject *parent, QQmlEngine* engine)
  : Node(parent, engine) {
    qDebug() << "Rectangle ctor";
    QQmlComponent rect(engine, ":/qml/Rectangle.qml");
    node = qobject_cast<QQuickItem*>(rect.create());
    node -> setParent(this);
}

/*---------------------------------------------------------------------------*/

Rectangle::~Rectangle() {
    qDebug() << "Rectangle dtor";
}

/*---------------------------------------------------------------------------*/

void Rectangle::appendChild(Node *child) {
    qDebug() << "Rectangle appendChild";
    node->childItems().append(child->getNode());
}

/*---------------------------------------------------------------------------*/

void Rectangle::removeChild(Node *child) {
    qDebug() << "Rectangle removeChild";
    node->childItems().removeOne(child->getNode());
}

/*---------------------------------------------------------------------------*/

void Rectangle::insertBefore(Node *child, Node *beforeChild) {
    qDebug() << "Rectangle insertBefore";
    node->childItems().insert(
        node->childItems().indexOf(beforeChild->getNode()),
        child->getNode()
    );
}

/*---------------------------------------------------------------------------*/

void Rectangle::commitUpdate(QMap<QString, QVariant> props) {
    qDebug() << "Rectangle commitUpdate";
    QMap<QString, QVariant>::iterator i = props.begin();
    while (i != props.end()) {
        node->setProperty(i.key().toStdString().c_str(),i.value());
        i++;
    }
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
