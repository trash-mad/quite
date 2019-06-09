#ifndef OBJECT_H
#define OBJECT_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>

namespace Quite {
namespace Base {

/*****************************************************************************/

class Object : public QObject{
  Q_OBJECT
  private:
    QJSValue _value;
  public:
    Object(QJSValue value, QObject* parent = nullptr);
    virtual ~Object();
    /*call(const QJSValueList &args = ...)
    QJSValue	callAsConstructor(const QJSValueList &args = ...)
    QJSValue	callWithInstance(const QJSValue &instance, const QJSValueList &args = ...)
    bool	deleteProperty(const QString &name)
    bool	equals(const QJSValue &other) const
    QJSValue::ErrorType	errorType() const
    bool	hasOwnProperty(const QString &name) const
    bool	hasProperty(const QString &name) const
    bool	isArray() const
    bool	isBool() const
    bool	isCallable() const
    bool	isDate() const
    bool	isError() const
    bool	isNull() const
    bool	isNumber() const
    bool	isObject() const
    bool	isQMetaObject() const
    bool	isQObject() const
    bool	isRegExp() const
    bool	isString() const
    bool	isUndefined() const
    bool	isVariant() const
    QJSValue	property(const QString &name) const
    QJSValue	property(quint32 arrayIndex) const
    QJSValue	prototype() const
    void	setProperty(const QString &name, const QJSValue &value)
    void	setProperty(quint32 arrayIndex, const QJSValue &value)
    void	setPrototype(const QJSValue &prototype)
    bool	strictlyEquals(const QJSValue &other) const
    bool	toBool() const
    QDateTime	toDateTime() const
    qint32	toInt() const
    double	toNumber() const
    const QMetaObject *	toQMetaObject() const
    QObject *	toQObject() const
    QString	toString() const
    quint32	toUInt() const
    QVariant	toVariant() const
    QJSValue &	operator=(QJSValue &&other)
    QJSValue &	operator=(const QJSValue &other)*/
};

/*****************************************************************************/

typedef QList<QSharedPointer<Object>> ObjectList;

/*****************************************************************************/

} // namespace Base
} // namespace Quite

#endif // OBJECT_H
