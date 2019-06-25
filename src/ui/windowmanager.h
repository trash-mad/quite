#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QtDebug>
#include <QObject>
#include <QThread>
#include <QList>

#include "src/ui/base/node.h"
#include "src/ui/base/component.h"
#include "src/ui/components/window.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {

/*****************************************************************************/

class WindowManager : public QObject {
  Q_OBJECT
  private:
    QList<Components::Window*> wins;
  public:
    explicit WindowManager(QObject* parent = nullptr);
    virtual ~WindowManager();
  public slots:
    void renderUi(Node* rootNode);
  private:
    Component* renderComponent(Node* node);
    Component* renderComponentTree(Node* node);
  signals:
    void closed();
};

/*****************************************************************************/

} // namespace Ui
} // namespace Quite

#endif // WINDOWMANAGER_H
