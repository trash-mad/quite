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

void InstallExtension::process(
    QObject* engine,
    QJSEngine *eval,
    QThreadPool *pool
) {
    (void)(pool);
    Base::Extension* ext = nullptr;

    switch (extension) {
        case Quite::Extension::TimerExtension:
            ext = new Quite::Extensions::TimerExtension(engine);
            break;
    }

    ext->install(
        eval->globalObject(),
        Base::Wrapper::fromQObject(engine, ext, eval)
    );
}

/*****************************************************************************/

} // namespace Events
} // namespace Quite
