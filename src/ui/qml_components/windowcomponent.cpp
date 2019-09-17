#include "windowcomponent.h"

namespace Quite {
namespace Ui {
namespace QmlComponents {

/*****************************************************************************/

WindowComponent::WindowComponent() {
    qDebug() << "WindowComponent ctor";
    window=new WindowComponentPrivate();
    setParentItem(window->contentItem());
    connect(window,SIGNAL(closed()),this,SIGNAL(closed()));
    connect(window,SIGNAL(resize()),this,SIGNAL(resize()));
    window->show();
}

/*---------------------------------------------------------------------------*/

WindowComponent::~WindowComponent() {
    qDebug() << "WindowComponent dtor";
    window->deleteLater();
}

/*---------------------------------------------------------------------------*/

void WindowComponent::commitWindowProps(QMap<QString, QVariant> props) {
    qDebug() << "WindowComponent commitWindowProps";
    QMap<QString,QVariant>::iterator iter;
    for(iter = props.begin(); iter!= props.end(); iter++) {
        QString name = iter.key();
        QVariant value = iter.value();
        if (name=="height") {
            window->setHeight(value.toInt());
        } else if (name=="width") {
            window->setWidth(value.toInt());
        } else {
            qCritical() << "WindowComponent commitWindowProps invalid prop";
        }
    }
}

/*---------------------------------------------------------------------------*/

int WindowComponent::getHeight() const {
    return window->size().height();
}

/*---------------------------------------------------------------------------*/

int WindowComponent::getWidth() const {
    return window->size().width();
}

/*****************************************************************************/

WindowComponentPrivate::WindowComponentPrivate() {
    installEventFilter(this);
}

/*---------------------------------------------------------------------------*/

bool WindowComponentPrivate::eventFilter(QObject *obj, QEvent *ev) {
    Q_UNUSED(obj)
    if (ev->type()==QEvent::Close) {
        emit closed();
    } else if (ev->type()==QEvent::Resize) {
        emit resize();
    }
    return false;
}

/*****************************************************************************/

} // namespace Components
} // namespace Ui
} // namespace Quite
