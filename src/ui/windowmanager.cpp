#include "windowmanager.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

WindowManager::WindowManager(QObject* parent)
  : QObject(parent) {
    qDebug() << "WindowManager ctor";
}

/*---------------------------------------------------------------------------*/

WindowManager::~WindowManager() {
    qDebug() << "WindowManager dtor";
}

/*---------------------------------------------------------------------------*/

void WindowManager::renderUi(Node *rootNode) {
    qDebug() << "WindowManager render";
    (void)(rootNode);
    emit closed();
}

/*****************************************************************************/

} // namespace Ui
} // namespace Quite
