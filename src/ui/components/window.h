#ifndef WINDOW_H
#define WINDOW_H

#include <QtDebug>
#include <QObject>
#include <QQuickWindow>

#include "src/ui/base/component.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class WindowPrivate : public QQuickWindow {
  Q_OBJECT
  protected:
    virtual bool event(QEvent* e) override;
  public:
    WindowPrivate();
    virtual ~WindowPrivate();
  signals:
    void closed();
};

/*****************************************************************************/

class Window : public Component{
  Q_OBJECT
  private:
    WindowPrivate window;
  public:
    Window(Node* node, QQmlEngine* engine);
    virtual ~Window();
    virtual void propsChanged(QMap<QString, QVariant> props);
    virtual void childChanged(QLinkedList<Component*> child);
    void show();
  signals:
    void closed();
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite

#endif // WINDOW_H
