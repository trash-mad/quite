#include "slider.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Slider::Slider(Node *node, QQmlEngine *engine, Element *parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Slider.qml")),
        node,
        engine,
        parent
    ){
    qDebug() << "Slider ctor";
    getItem()->setHeight(45);
    getItem()->setWidth(125);
}

/*---------------------------------------------------------------------------*/

Slider::~Slider() {
    qDebug() << "Slider dtor";
}

/*---------------------------------------------------------------------------*/

void Slider::onElementValueChanged(QVariant value) {
    QMap<QString, QVariant> props = getProps();
    Invoke* obj = nullptr;
    if (!props.contains("valueChanged")) {
        return;
    } else {
        QVariant callBack = props["valueChanged"];
        if (Invoke::tryCast(callBack, obj)) {
            qDebug() << "Slider valueChanged" << value.toString();
            obj->addArgs({value});
            emit invoke(obj);
        } else {
            qCritical() << "Slider valueChanged not callable";
        }
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
