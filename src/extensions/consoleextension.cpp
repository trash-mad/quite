#include "consoleextension.h"

namespace Quite {
namespace Extensions {

/*****************************************************************************/

ConsoleExtension::ConsoleExtension(QObject* parent)
  : Extension(parent) {
    qDebug() << "ConsoleExtension ctor";
}

/*---------------------------------------------------------------------------*/

ConsoleExtension::~ConsoleExtension() {
    qDebug() << "ConsoleExtension dtor";
}

/*---------------------------------------------------------------------------*/

void ConsoleExtension::install(
    QJSValue global,
    QJSValue current,
    QJSEngine* eval) {
    (void)(eval);
    qDebug() << "ConsoleExtension install";
    global.setProperty("console",current);
}

/*---------------------------------------------------------------------------*/

QJSValue ConsoleExtension::log(QJSValue msg) {
    //qInfo() << msg.toString();
    std::cout << msg.toString().toStdString() << "\n";
    return QJSValue();
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
