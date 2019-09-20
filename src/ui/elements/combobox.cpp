#include "combobox.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

ComboBox::ComboBox(Node* node, QQmlEngine* engine, Element* parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/ComboBox.qml")),
        node,
        engine,
        parent
    ) {
    qDebug() << "ComboBox ctor";
    getItem()->setProperty("preferredHeight",45);
    getItem()->setProperty("preferredWidth",125);
}

/*---------------------------------------------------------------------------*/

ComboBox::~ComboBox() {
    qDebug() << "ComboBox dtor";
}

/*---------------------------------------------------------------------------*/

void ComboBox::onElementSelectionChanged(int index) {
    QMap<QString, QVariant> props = getProps();
    Invoke* obj = nullptr;
    if (!props.contains("onSelectionChanged")) {
        return;
    } else {
        QVariant callBack = props["onSelectionChanged"];
        if (Invoke::tryCast(callBack, obj)) {
            qDebug() << "ComboBox selectionChanged" << index;
            obj->addArgs({index});
            emit invoke(obj);
        } else {
            qCritical() << "ComboBox selectionChanged not callable";
        }
    }
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
