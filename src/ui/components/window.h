#ifndef WINDOW_H
#define WINDOW_H

#include <QEvent>
#include <QtDebug>
#include <QObject>
#include <QQuickView>
#include <QQuickWindow>

#include "src/ui/node.h"

namespace Quite {
namespace Ui {
namespace Components {

/*****************************************************************************/

class WindowPrivate : public QQuickWindow {
  private:
    bool opened = false;
    bool closed = false;
  protected:
    virtual bool event(QEvent* e) override;
  public:
    WindowPrivate();
    virtual ~WindowPrivate();
    bool isClosed() const;
    bool isOpened() const;
};

/*****************************************************************************/

class Window : public Node {
  private:
    WindowPrivate *window;
  protected:
    virtual void appendChild(Node* child);
    virtual void removeChild(Node* child);
    virtual void insertBefore(Node* child, Node* beforeChild);
    virtual void commitUpdate(QMap<QString, QVariant> props);
  public:
    Window(QObject *parent, QQmlEngine* engine);
    virtual ~Window();
    bool isClosed() const;
    bool isOpened() const;
    void show();
};

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite

#endif // WINDOW_H
