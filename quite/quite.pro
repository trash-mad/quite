QT += core gui widgets qml
TARGET = quite
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += main.cpp \
    base/engine.cpp \
    application.cpp \
    base/event.cpp
HEADERS  += \
    base/engine.h \
    application.h \
    base/event.h
