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

QJSValue QuiteExtension::render(QJSValue windowComponent) {
    qDebug() << "QuiteExtension render";

    Window* window = nullptr;

    if(!tryCastWindow(windowComponent, window)) {
        QCoreApplication::sendEvent(parent(), new Events::ThrowError(
            "render: argument not window"
        ));
    } else {
        QCoreApplication::sendEvent(parent(), new Events::Await(
            new WindowMonitor(window)
        ));
        window->show();
    }

    return QJSValue();
}

/*---------------------------------------------------------------------------*/

QJSValue QuiteExtension::createElement(
    QJSValue name,
    QJSValue props,
    QJSValue child
) {
    (void)(props);
    (void)(child);
    qDebug() << "QuiteExtension createElement";

    QString component = name.toString();
    Node* node = nullptr;
    QJSValue result = QJSValue(QJSValue::SpecialValue::NullValue);

    if(component == "Window") {
        node = new Window(nullptr, engine);
    } else if(component == "Rectangle") {
        node = new Rectangle(nullptr, engine);
    } else {
        QCoreApplication::sendEvent(parent(), new Events::ThrowError(
            "createComponent: invalid name parameter"
        ));
    }

    if(node!=nullptr) {
        result = factory->newQObject(node);

        if(!child.isUndefined()){
            node->appendChild(child);
        }

        if(!props.isNull()){
            node->commitUpdate(props);
        }
    }

    return result;
}

/*---------------------------------------------------------------------------*/

bool QuiteExtension::tryCastWindow(QJSValue src, Window *&dst) {
    if(!src.isObject()) {
        return false;
    } else {
        dst = dynamic_cast<Window*>(src.toQObject());
        return dst!=nullptr;
    }
}

/*****************************************************************************/

} // namespace Extensions
} // namespace Quite
