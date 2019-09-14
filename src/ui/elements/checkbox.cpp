#include "checkbox.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

CheckBox::CheckBox(Node *node, QQmlEngine *engine, Element *parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/CheckBox.qml")),
        node,
        engine,
        parent
    ){
    qDebug() << "CheckBox ctor";
    getItem()->setHeight(45);
    getItem()->setWidth(45);
}

/*---------------------------------------------------------------------------*/

CheckBox::~CheckBox() {
    qDebug() << "CheckBox dtor";
}

/*---------------------------------------------------------------------------*/

void CheckBox::onCheck(bool enabled) {
    QMap<QString, QVariant> props = getProps();
    Invoke* obj = nullptr;
    if (!props.contains("onCheck")) {
        return;
    } else {
        QVariant callBack = props["onCheck"];
        if (Invoke::tryCast(callBack, obj)) {
            qDebug() << "CheckBox onCheck" << enabled;
            obj->addArgs({enabled});
            emit invoke(obj);
        } else {
            qCritical() << "CheckBox onCheck not callable";
        }
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
