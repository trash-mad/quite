#ifndef WINDOWCOMPONENT_H
#define WINDOWCOMPONENT_H

#include <QTimer>
#include <QThread>
#include <QtDebug>
#include <QObject>
#include <QQuickItem>
#include <QResizeEvent>
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
    void resize();
};

/*****************************************************************************/

class WindowComponent : public QQuickItem {
  Q_OBJECT
  private:
    WindowComponentPrivate *window;
  public:
    WindowComponent();
    virtual ~WindowComponent() override;
  public:
    int getHeight() const;
    int getWidth() const;
  signals:
    void closed();
    void resize();
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite


#endif // WINDOWCOMPONENT_H
