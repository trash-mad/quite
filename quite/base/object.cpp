#include "object.h"

namespace Quite {
namespace Base {

Object::Object(QJSValue value, QObject* parent)
  : QObject(parent) {
    qDebug() << "Object ctor";
    this->_value = value;
}

Object::~Object() {
    qDebug() << "Object dtor";
}

} // namespace Base
} // namespace Quites

