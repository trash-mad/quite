#include "quiteextension.h"

namespace Quite {
namespace Extensions {

/*****************************************************************************/

QuiteExtension::QuiteExtension(QObject* parent)
  : Extension(parent) {
    qDebug() << "QuiteExtension ctor";
    engine = new QQmlEngine(this);
}

/*---------------------------------------------------------------------------*/

QuiteExtension::~QuiteExtension() {
    qDebug() << "QuiteExtension dtor";
    factory->deleteLater();
    engine->deleteLater();
}

/*---------------------------------------------------------------------------*/

void QuiteExtension::install(
    QJSValue global,
    QJSValue current,
    Factory* factory
) {
    qDebug() << "QuiteExtension install";
    global.setProperty("Quite", current);
    this->factory = factory;
}

/*---------------------------------------------------------------------------*/

QJSValue QuiteExtension::render(QJSValue windowComponent)
{

}

/*---------------------------------------------------------------------------*/

QJSValue QuiteExtension::createComponent(QJSValue name) {
    QString component = name.toString();
    QJSValue result;
    if(component == "Window") {
        result = factory->newQObject(new Window(this, engine));
    } /* else if(){

    } */ else {
        QCoreApplication::sendEvent(parent(), new Events::ThrowError(
            "createComponent: invalid name parameter"
        ));
    }
    return result;
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
