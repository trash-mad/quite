#ifndef IMPORTMODULE_H
#define IMPORTMODULE_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QCoreApplication>

#include "base/event.h"
#include "events/eval.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

class ImportModule : public Base::Event{
  private:
    QString path;
  public:
    explicit ImportModule(QString path="");
    virtual ~ImportModule();
    virtual void process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // IMPORTMODULE_H
