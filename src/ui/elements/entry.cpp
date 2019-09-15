#include "entry.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

Entry::Entry(Node *node, QQmlEngine *engine, Element *parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Entry.qml")),
        node,
        engine,
        parent
    ){
    qDebug() << "Entry ctor";
    getItem()->setHeight(45);
    getItem()->setWidth(125);
}

/*---------------------------------------------------------------------------*/

Entry::~Entry() {
    qDebug() << "Entry dtor";
}

/*---------------------------------------------------------------------------*/

void Entry::onElementValueChanged(QVariant value) {
    QMap<QString, QVariant> props = getProps();
    Invoke* obj = nullptr;
    if (!props.contains("textChanged")) {
        return;
    } else {
        QVariant callBack = props["textChanged"];
        if (Invoke::tryCast(callBack, obj)) {
            qDebug() << "Entry textChanged" << value.toString();
            obj->addArgs({value});
            emit invoke(obj);
        } else {
            qCritical() << "Entry textChanged not callable";
        }
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
