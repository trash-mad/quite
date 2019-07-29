#include "component.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Component::Component(ComponentNode* node, QQmlEngine* engine, Element* parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Component.qml")),
        node,
        engine,
        parent
    ) {
    qDebug() << "Component ctor";
    connect(
        node,
        SIGNAL(renderSubtree(Node*)),
        this,
        SLOT(renderSubtreeHandler(Node*))
    );
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

void Component::resolveManagerActions(Element *root) {
    while (!root->ready()) {
        qDebug() << "Component resolveManagerActions await";
        QCoreApplication::processEvents();
    }
    QLinkedList<Element*> child=root->getChild();
    QLinkedList<Element*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        resolveManagerActions(*iter);
    }
}

/*---------------------------------------------------------------------------*/

void Component::renderSubtreeHandler(Node *child) {
    if (!diffImposible) {
        diffImposible=true;
        qInfo()
            << "Diff rendering is impossible."
            << "The sequence contains a list of items without a key prop";
    }
    emit renderSubtree(child);
}

/*****************************************************************************/

} // namespace Ui
} // namespa Quite
