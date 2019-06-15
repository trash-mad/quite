QT += core qml
TARGET = quite
TEMPLATE = app
CONFIG += c++17
DEFINES += QT_DEPRECATED_WARNINGS

lessThan(QT_MAJOR_VERSION, 5) : error("requires Qt > 5.12.*")
equals(QT_MAJOR_VERSION, 5) : lessThan(QT_MINOR_VERSION, 12) : error("requires Qt > 5.12.*")

SOURCES += main.cpp \
    events/eval.cpp \
    base/emitter.cpp
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
    events/eval.h \
    base/emitter.h
HEADERS += application.h
HEADERS += base/event.h
HEADERS += base/extension.h
HEADERS += base/wrapper.h
HEADERS += extensions/timerextension.h
HEADERS += events/installextension.h
HEADERS += events/importmodule.h
HEADERS += events/throwerror.h
