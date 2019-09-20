#ifndef CONSOLEPROVIDER_H
#define CONSOLEPROVIDER_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QQmlEngine>

namespace Quite {
namespace Ui {
namespace QmlProviders {

/*****************************************************************************/

class ConsoleProvider: public QObject {
  Q_OBJECT
  public:
    explicit ConsoleProvider(QObject* parent=nullptr);
    virtual ~ConsoleProvider();
  public slots:
    void logInternal(QStringList msg);
    void warnInternal(QStringList msg);
    void infoInternal(QStringList msg);
    void criticalInternal(QStringList msg);
  public:
    static QJSValue initSingletonType(QQmlEngine *qml, QJSEngine *js);
};

/*****************************************************************************/

} // namespace Providers
} // namespace Ui
} // namespace Quite

#endif // CONSOLEPROVIDER_H
