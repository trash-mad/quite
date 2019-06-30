#include "installextension.h"

namespace Quite {
namespace Events {

/*****************************************************************************/

InstallExtension::InstallExtension(Quite::Extension extension) {
    qDebug() << "InstallExtension ctor";
    this->extension = extension;
}

/*---------------------------------------------------------------------------*/

InstallExtension::~InstallExtension() {
    qDebug() << "InstallExtension dtor";
}

/*---------------------------------------------------------------------------*/

EventResult InstallExtension::process(
    QObject* engine,
    QJSEngine* eval,
    QThreadPool *pool
) {
    (void)(eval);
    Base::Extension* ext = nullptr;

    switch (extension) {
        case Quite::Extension::TimerExtension:
            ext = new Quite::Extensions::TimerExtension(engine);
            break;
        case Quite::Extension::ConsoleExtension:
            ext = new Quite::Extensions::ConsoleExtension(engine);
            break;
        case Quite::Extension::QuiteExtension:
            ext = new Quite::Extensions::QuiteExtension(engine);
            break;
    }

    ext->install(
        eval->globalObject(),
        Base::Wrapper::fromQObject(engine, ext, eval),
        eval
    );

    return EventResult::Ok;
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
