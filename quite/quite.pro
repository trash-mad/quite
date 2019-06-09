QT += core qml testlib
TARGET = quite
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += main.cpp \
    base/engine.cpp \
    application.cpp \
    base/event.cpp \
    base/extension.cpp \
    base/object.cpp \
    base/wrapper.cpp
HEADERS  += \
    base/engine.h \
    application.h \
    base/event.h \
    base/extension.h \
    base/object.h \
    base/wrapper.h
