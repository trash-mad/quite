#include "extension.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Extension::Extension(Engine* engine)
  : QObject(engine) {
    qDebug() << "Extension ctor";
    _engine = engine;
}

/*---------------------------------------------------------------------------*/

Extension::~Extension() {
    qDebug() << "Extension dtor";
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
