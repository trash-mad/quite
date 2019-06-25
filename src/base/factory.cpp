#include "factory.h"

namespace Quite {
namespace Base {

/*****************************************************************************/

Factory::Factory(QObject* parent, QJSEngine* eval)
  : QObject(parent) {
    qDebug() << "Factory ctor";
    this->eval = eval;
}

/*---------------------------------------------------------------------------*/

Factory::~Factory() {
    qDebug() << "Factory dtor";
}

/*---------------------------------------------------------------------------*/

QJSValue Factory::newQObject(QObject *object) {
    return eval->newQObject(object);
}

/*---------------------------------------------------------------------------*/

QJSValue Factory::newArray(uint lenght) {
    return eval->newArray(lenght);
}

/*****************************************************************************/

} // namespace Base
} // namespace Quite
