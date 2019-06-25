QT += core qml quick quickcontrols2
TARGET = quite
TEMPLATE = app
CONFIG += c++17
CONFIG += console
DEFINES += QT_DEPRECATED_WARNINGS

lessThan(QT_MAJOR_VERSION, 5) : error("requires Qt > 5.12.*")
equals(QT_MAJOR_VERSION, 5) : lessThan(QT_MINOR_VERSION, 12) : error("requires Qt > 5.12.*")

SOURCES += src/main.cpp \
    src/events/renderui.cpp \
    src/ui/base/component.cpp \
    src/ui/base/node.cpp \
    src/ui/windowmanager.cpp \
    src/ui/components/window.cpp
SOURCES += src/extensions/quiteextension.cpp 
SOURCES += src/base/factory.cpp
SOURCES += src/events/eval.cpp
SOURCES += src/base/emitter.cpp
SOURCES += src/base/monitor.cpp
SOURCES += src/events/await.cpp
SOURCES += src/monitors/timermonitor.cpp
SOURCES += src/extensions/consoleextension.cpp
SOURCES += src/base/engine.cpp
SOURCES += src/application.cpp
SOURCES += src/base/event.cpp
SOURCES += src/base/extension.cpp
SOURCES += src/base/wrapper.cpp
SOURCES += src/extensions/timerextension.cpp
SOURCES += src/events/installextension.cpp
SOURCES += src/events/importmodule.cpp
SOURCES += src/events/throwerror.cpp

HEADERS += src/base/engine.h \
    src/events/renderui.h \
    src/ui/base/component.h \
    src/ui/base/node.h \
    src/ui/windowmanager.h \
    src/ui/components/window.h
HEADERS += src/extensions/quiteextension.h 
HEADERS += src/base/factory.h
HEADERS += src/events/eval.h
HEADERS += src/base/emitter.h
HEADERS += src/base/monitor.h
HEADERS += src/events/await.h
HEADERS += src/monitors/timermonitor.h
HEADERS += src/extensions/consoleextension.h
HEADERS += src/application.h
HEADERS += src/base/event.h
HEADERS += src/base/extension.h
HEADERS += src/base/wrapper.h
HEADERS += src/extensions/timerextension.h
HEADERS += src/events/installextension.h
HEADERS += src/events/importmodule.h
HEADERS += src/events/throwerror.h

RESOURCES += res.qrc
