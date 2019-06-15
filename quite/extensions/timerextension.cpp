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

void TimerExtension::install(QJSValue global, QJSValue current) {
    qDebug() << "TimerExtension install";
    global.setProperty("setTimeout",current.property("setTimeout"));
}

QJSValue TimerExtension::setTimeout(QJSValue handler, QJSValue timeout) {
    qDebug() << ")))))))))))))))))))))))))))))))))))))))))))))))";
    return QJSValue();
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
