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
    connect(
        node,
        SIGNAL(renderDiff()),
        this,
        SLOT(updateLayout())
    );
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

void Component::updateLayoutNow() {
    qDebug() << "Component updateLayoutNow";
    Element::updateLayoutNow(
        static_cast<int>(getItem()->height()),
        static_cast<int>(getItem()->width())
    );
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
