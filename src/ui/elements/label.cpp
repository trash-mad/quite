#include "label.h"

namespace Quite {
namespace Ui {
namespace Elements {


/*****************************************************************************/

Label::Label(Node *node, QQmlEngine *engine, Element *parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Label.qml")),
        node,
        engine,
        parent
    ) {
    qDebug() << "Label ctor";
    getItem()->setProperty("preferredHeight",45);
    getItem()->setProperty("preferredWidth",125);
}

/*---------------------------------------------------------------------------*/

Label::~Label() {
    qDebug() << "Label dtor";
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
