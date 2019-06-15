#ifndef TIMERMONITOR_H
#define TIMERMONITOR_H

#include <QTimer>
#include <QtDebug>
#include <QObject>
#include <QJSValue>

namespace Quite {
namespace Objects {

/*****************************************************************************/

class TimerMonitor : public QObject {
  Q_OBJECT
  private:
    QTimer* timer;
    QJSValue func;
    qint32 id;
  public:
    TimerMonitor(QObject* parent, QTimer* timer, QJSValue func, qint32 id);
    virtual ~TimerMonitor();
    bool isActive() const;
  public slots:
    void timeout();
  signals:
    void done(qint32 id);
};

/*****************************************************************************/

} // namespace Objects
} // namespace Quite

#endif // TIMERMONITOR_H
