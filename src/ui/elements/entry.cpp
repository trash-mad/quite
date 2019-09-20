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
    getItem()->setProperty("preferredHeight",45);
    getItem()->setProperty("preferredWidth",125);
}

/*---------------------------------------------------------------------------*/

Entry::~Entry() {
    qDebug() << "Entry dtor";
}

/*---------------------------------------------------------------------------*/

void Entry::onElementValueChanged(QVariant value) {
    QMap<QString, QVariant> props = getProps();
    Invoke* obj = nullptr;
    if (!props.contains("onTextChanged")) {
        return;
    } else {
        QVariant callBack = props["onTextChanged"];
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
