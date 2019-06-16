#ifndef IMPORTMODULE_H
#define IMPORTMODULE_H

#include <QDir>
#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QCoreApplication>

#include "base/event.h"
#include "events/eval.h"

using namespace Quite::Base;

namespace Quite {
namespace Events {

/*****************************************************************************/

class ImportModule : public Base::Event{
  private:
    QString path;
  public:
    explicit ImportModule(QString path="");
    virtual ~ImportModule();
    virtual EventResult process(
        QObject* engine,
        QJSEngine* eval,
        QThreadPool* pool
    );
};

/*****************************************************************************/

} // namespace Events
} // namespace Quite

#endif // IMPORTMODULE_H
