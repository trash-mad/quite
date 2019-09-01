#ifndef ENGINE_H
#define ENGINE_H

#include <QStack>
#include <QObject>
#include <QtDebug>
#include <QThread>
#include <QJSValue>
#include <QVariant>
#include <QJSEngine>
#include <QEventLoop>
#include <QThreadPool>
#include <QJSValueIterator>

#include "src/base/event.h"
#include "src/events/eval.h"
#include "src/base/monitor.h"
#include "src/events/await.h"
#include "src/ui/base/node.h"
#include "src/ui/base/dialog.h"
#include "src/objects/invoke.h"
#include "src/events/renderui.h"
#include "src/events/renderdialog.h"

using namespace Quite::Ui::Base;
using namespace Quite::Objects;
using namespace Quite::Events;

namespace Quite {
namespace Base {

/*****************************************************************************/

class Engine : public QThread {
  Q_OBJECT
  private:
    QStack<Monitor*>* rethrow;
    QThreadPool* pool;
    QJSEngine* eval;
    bool uiexec;
  public:
    explicit Engine(QObject *parent = nullptr);
    virtual ~Engine();
  protected:
    virtual void run();
    virtual bool event(QEvent* event);
  public slots:
    void invokeHandler(Invoke* o);
    void windowClosed();
  signals:
    void done();
    void renderUi(Node* rootNode);
    void renderDialog(IDialog* dialog);
};

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // ENGINE_H
