#include "timerextension.h"

namespace Quite {
namespace Extensions {

/*****************************************************************************/

TimerExtension::TimerExtension(QObject *parent)
  : Extension(parent) {
    qDebug() << "TimerExtension ctor";
}

/*---------------------------------------------------------------------------*/

TimerExtension::~TimerExtension() {
    qDebug() << "TimerExtension dtor";
}

/*---------------------------------------------------------------------------*/

void TimerExtension::install(
    const QJSValue &global,
    const QJSValue &current
) {
    qDebug() << "install";

    QJSValueIterator it(current);
    while (it.hasNext()) {
        it.next();
        qInfo() << it.name();
    }
}

void TimerExtension::setTimeout(QJSValue handler, QJSValue timeout) {
    qDebug() << ")))))))))))))))))))))))))))))))))))))))))))))))";
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
