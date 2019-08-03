#ifndef RENDERSYNCHRONIZER_H
#define RENDERSYNCHRONIZER_H

#include <QtDebug>
#include <QObject>
#include <QMutex>

namespace Quite {
namespace Ui {

/*****************************************************************************/

class RenderSynchronizer : public QObject {
  Q_OBJECT
  private:
    bool rendering=false;
    int resolveCounter=0;
    QMutex locker;
  private:
    explicit RenderSynchronizer();
    virtual ~RenderSynchronizer();
  public:
    bool tryIncrementCounter(QString from);
    void decrementCounter(QString from);
    Q_DECL_DEPRECATED bool tryBeginRender();
    Q_DECL_DEPRECATED void endRender();
    bool changesResolved();
  public:
    static RenderSynchronizer* instance();
};

/*****************************************************************************/

} // namespace Ui
} // namespace Quite

#endif // RENDERSYNCHRONIZER_H
