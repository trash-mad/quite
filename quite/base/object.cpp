#include "object.h"

namespace Quite {
namespace Base {

Object::Object(QJSValue value, QObject* parent, QObject* engine)
  : QObject(parent) {
    qDebug() << "Object ctor";
    this->_value = value;
    this->_engine = engine;
}

Object::~Object() {
    qDebug() << "Object dtor";
}

} // namespace Base
} // namespace Quites

