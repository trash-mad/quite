#ifndef DIALOG_H
#define DIALOG_H

#include <QtDebug>
#include <QObject>
#include <QJSValue>
#include <QVariant>
#include <QJSEngine>
#include <QEventLoop>

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

class DialogResolver : public QObject {
  Q_OBJECT
  private:
    QVariant result;
  public:
    explicit DialogResolver(QObject* parent=nullptr);
    virtual ~DialogResolver();
  public:
    void resolve(QVariant result);
    QVariant getResult() const;
  signals:
    void resolved();
};

/*****************************************************************************/

struct IDialog {
  public:
    virtual ~IDialog();
    virtual QJSValue exec(
        QJSEngine* engine
    ) = 0;
    virtual void show() = 0;
};

/*****************************************************************************/

template <typename ReturnValue>
class Dialog : public virtual IDialog {
  private:
    DialogResolver resolver;
    int resultType;
  public:
    Dialog();
    virtual ~Dialog() override;
  public:
    virtual QJSValue exec(
        QJSEngine* engine
    ) override;
    void resolve(ReturnValue result);
};

/*****************************************************************************/

/* alert(string):string,  */
extern template class Dialog<QString>;

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite

#endif // DIALOG_H
