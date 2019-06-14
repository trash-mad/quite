#include "extension.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Extension::Extension(QObject* parent)
  : QObject(parent) {
    qDebug() << "Extension ctor";
}

/*---------------------------------------------------------------------------*/

Extension::~Extension() {
    qDebug() << "Extension dtor";
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
