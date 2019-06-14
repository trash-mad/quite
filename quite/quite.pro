QT += core qml testlib
TARGET = quite
TEMPLATE = app
CONFIG += c++17
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += main.cpp \
    base/engine.cpp \
    application.cpp \
    base/event.cpp \
    base/extension.cpp \
    base/wrapper.cpp \
    extensions/timerextension.cpp \
    events/installextension.cpp
HEADERS  += \
    base/engine.h \
    application.h \
    base/event.h \
    base/extension.h \
    base/wrapper.h \
    extensions/timerextension.h \
    events/installextension.h
