#ifndef WINDOW_H
#define WINDOW_H

#include <QtDebug>
#include <QObject>
#include <QQuickWindow>

#include "src/ui/base/element.h"

using namespace Quite::Ui::Base;

namespace Quite {
namespace Ui {
namespace Elements {

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

class Window : public Element {
  Q_OBJECT
  private:
    WindowPrivate window;
  public:
    Window(Node* node, QQmlEngine* engine, Element* parent);
    virtual ~Window();
  signals:
    void closed();
};

/*****************************************************************************/

} // namespace Elements
} // namespace Ui
} // namespace Quite

#endif // WINDOW_H
