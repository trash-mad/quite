#ifndef WINDOWCOMPONENT_H
#define WINDOWCOMPONENT_H

#include <QtDebug>
#include <QObject>
#include <QQuickItem>
#include <QQuickWindow>

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class WindowComponentPrivate : public QQuickWindow {
  Q_OBJECT
  protected:
    virtual bool event(QEvent* e) override;
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
