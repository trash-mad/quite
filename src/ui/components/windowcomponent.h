#ifndef WINDOWCOMPONENT_H
#define WINDOWCOMPONENT_H

#include <QTimer>
#include <QThread>
#include <QtDebug>
#include <QObject>
#include <QQuickItem>
#include <QQuickWindow>

#include "src/ui/base/diffcounter.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class WindowComponentPrivate : public QQuickWindow {
  Q_OBJECT
  public:
    WindowComponentPrivate();
  protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
  signals:
    void closed();
};

/*****************************************************************************/

class WindowComponent : public QQuickItem {
  Q_OBJECT
  private:
    WindowComponentPrivate window;
  public:
    WindowComponent();
    virtual ~WindowComponent() override;
    QQuickItem* contentItem() const;
  signals:
    void closed();
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite


#endif // WINDOWCOMPONENT_H
