#include "consoleprovider.h"

namespace Quite {
namespace Ui {
namespace QmlProviders {

/*****************************************************************************/

ConsoleProvider::ConsoleProvider(QObject* parent)
  : QObject(parent) {
    qDebug() << "ConsoleProvider ctor";
}

/*---------------------------------------------------------------------------*/

ConsoleProvider::~ConsoleProvider() {
    qDebug() << "ConsoleProvider dtor";
}

/*---------------------------------------------------------------------------*/

void ConsoleProvider::logInternal(QStringList msg) {
    qDebug() << msg.join("");
}

/*---------------------------------------------------------------------------*/

void ConsoleProvider::warnInternal(QStringList msg) {
    qWarning() << msg.join("");
}

/*---------------------------------------------------------------------------*/

void ConsoleProvider::infoInternal(QStringList msg) {
    qInfo() << msg.join("");
}

/*---------------------------------------------------------------------------*/

void ConsoleProvider::criticalInternal(QStringList msg) {
    qCritical() << msg.join("");
}

/*---------------------------------------------------------------------------*/

QJSValue ConsoleProvider::initSingletonType(
    QQmlEngine *qml,
    QJSEngine *js
) {
    qDebug() << "ConsoleProvider initSingletonType";
    QJSValue instance=js->newQObject(new ConsoleProvider(qml));
    QJSValue restProvider=js->evaluate(
        "(function (instance) {" \
        "   instance.log=function(...log){" \
        "       return instance.logInternal(log);" \
        "   }; " \
        "   instance.debug=function(...log){" \
        "       return instance.logInternal(log);" \
        "   }; " \
        "   instance.warn=function(...log){" \
        "       return instance.warnInternal(log);" \
        "   }; " \
        "   instance.critical=function(...log){" \
        "       return instance.criticalInternal(log);" \
        "   }; " \
        "   instance.info=function(...log){" \
        "       return instance.infoInternal(log);" \
        "   }; " \
        "   return instance;" \
        "})"
    );
    if (restProvider.isError()) {
        qCritical() << restProvider.toString();
        return QJSValue();
    } else {
        QJSValue result=restProvider.call({instance});
        if (result.isError()) {
            qCritical() << result.toString();
            return QJSValue();
        } else {
            return instance;
        }
    }
}

/*****************************************************************************/

} // namespace QmlProviders
} // namespace Ui
} // namespace Quite
