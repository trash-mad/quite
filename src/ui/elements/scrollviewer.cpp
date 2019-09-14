#include "scrollviewer.h"

namespace Quite {
namespace Ui {
namespace Elements {

/*****************************************************************************/

ScrollViewer::ScrollViewer(Node *node, QQmlEngine *engine, Element *parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/ScrollViewer.qml")),
        node,
        engine,
        parent
    ) {
    qDebug() << "ScrollViewer ctor";
}

/*---------------------------------------------------------------------------*/

ScrollViewer::~ScrollViewer() {
    qDebug() << "ScrollViewer dtor";
}

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite
