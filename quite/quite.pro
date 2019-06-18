QT += core qml quick quickcontrols2
TARGET = quite
TEMPLATE = app
CONFIG += c++17
CONFIG += console
DEFINES += QT_DEPRECATED_WARNINGS

lessThan(QT_MAJOR_VERSION, 5) : error("requires Qt > 5.12.*")
equals(QT_MAJOR_VERSION, 5) : lessThan(QT_MINOR_VERSION, 12) : error("requires Qt > 5.12.*")

SOURCES += main.cpp \
    ui/node.cpp \
    ui/components/window.cpp \
    extensions/quiteextension.cpp \
    base/factory.cpp
SOURCES += events/eval.cpp
SOURCES += base/emitter.cpp
SOURCES += base/monitor.cpp
SOURCES += events/await.cpp
SOURCES += monitors/timermonitor.cpp
SOURCES += extensions/consoleextension.cpp
SOURCES += base/engine.cpp
SOURCES += application.cpp
SOURCES += base/event.cpp
SOURCES += base/extension.cpp
SOURCES += base/wrapper.cpp
SOURCES += extensions/timerextension.cpp
SOURCES += events/installextension.cpp
SOURCES += events/importmodule.cpp
SOURCES += events/throwerror.cpp

HEADERS += base/engine.h \
    ui/node.h \
    ui/components/window.h \
    extensions/quiteextension.h \
    base/factory.h
HEADERS += events/eval.h
HEADERS += base/emitter.h
HEADERS += base/monitor.h
HEADERS += events/await.h
HEADERS += monitors/timermonitor.h
HEADERS += extensions/consoleextension.h
HEADERS += application.h
HEADERS += base/event.h
HEADERS += base/extension.h
HEADERS += base/wrapper.h
HEADERS += extensions/timerextension.h
HEADERS += events/installextension.h
HEADERS += events/importmodule.h
HEADERS += events/throwerror.h
