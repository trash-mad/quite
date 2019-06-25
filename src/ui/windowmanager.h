#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QtDebug>
#include <QObject>

#include "src/ui/base/node.h"
#include "src/ui/base/component.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {

/*****************************************************************************/

class WindowManager : public QObject {
  Q_OBJECT
  public:
    explicit WindowManager(QObject* parent = nullptr);
    virtual ~WindowManager();
  public slots:
    void renderUi(Node* rootNode);
  signals:
    void closed();
};

/*****************************************************************************/

} // namespace Ui
} // namespace Quite

#endif // WINDOWMANAGER_H
