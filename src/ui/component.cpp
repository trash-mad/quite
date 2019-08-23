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

void Component::updateLayout(bool fill) {
    qDebug() << "Component updateLayout";
    Q_UNUSED(fill);
    Element::updateLayout(true);
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
