QT += core qml quick gui quickcontrols2 quickwidgets
TARGET = quite
TEMPLATE = app
CONFIG += c++17
CONFIG += console
CONFIG += rtti
DEFINES += QT_DEPRECATED_WARNINGS

lessThan(QT_MAJOR_VERSION, 5) : error("requires Qt > 5.12.*")
equals(QT_MAJOR_VERSION, 5) : lessThan(QT_MINOR_VERSION, 12) : error("requires Qt > 5.12.*")

win32-msvc* {
    MSVC_VER = $$(VisualStudioVersion)
    lessThan(MSVC_VER, 16.0){
        error("requires msvc 16.1 and greater (Visual Studio 2019)")
    }
}

SOURCES += src/main.cpp \
    3rdparty/yoga/event/yogaevent.cpp \
    3rdparty/yoga/yogalog.cpp \
    src/ui/flex/flexnode.cpp
SOURCES += src/objects/invoke.cpp
SOURCES += src/ui/base/diffcounter.cpp
SOURCES += src/ui/components/windowcomponent.cpp
SOURCES += src/events/renderui.cpp
SOURCES += src/objects/nodestruct.cpp
SOURCES += src/ui/base/componentnode.cpp
SOURCES += src/ui/base/element.cpp
SOURCES += src/ui/base/node.cpp
SOURCES += src/ui/component.cpp
SOURCES += src/ui/elements/button.cpp
SOURCES += src/ui/elements/rectangle.cpp
SOURCES += src/ui/elements/window.cpp
SOURCES += src/ui/manager.cpp
SOURCES += src/extensions/quiteextension.cpp 
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
    3rdparty/yoga/event/yogaevent.h \
    3rdparty/yoga/yogalog.h \
    src/ui/flex/flexnode.h
HEADERS += src/objects/invoke.h
HEADERS += src/ui/base/diffcounter.h
HEADERS += src/ui/components/windowcomponent.h
HEADERS += src/ui/elements/button.h
HEADERS += src/ui/elements/rectangle.h
HEADERS += src/ui/elements/window.h
HEADERS += src/ui/manager.h
HEADERS += src/events/renderui.h
HEADERS += src/objects/nodestruct.h
HEADERS += src/ui/base/componentnode.h
HEADERS += src/ui/base/element.h
HEADERS += src/ui/base/node.h
HEADERS += src/ui/component.h
HEADERS += src/extensions/quiteextension.h 
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

SOURCES += 3rdparty/yoga/Utils.cpp
SOURCES += 3rdparty/yoga/YGConfig.cpp
SOURCES += 3rdparty/yoga/YGEnums.cpp
SOURCES += 3rdparty/yoga/YGLayout.cpp
SOURCES += 3rdparty/yoga/YGNode.cpp
SOURCES += 3rdparty/yoga/YGNodePrint.cpp
SOURCES += 3rdparty/yoga/YGStyle.cpp
SOURCES += 3rdparty/yoga/YGValue.cpp
SOURCES += 3rdparty/yoga/Yoga.cpp
SOURCES +=
SOURCES +=
SOURCES +=
SOURCES +=

HEADERS += 3rdparty/yoga/CompactValue.h
HEADERS += 3rdparty/yoga/Utils.h
HEADERS += 3rdparty/yoga/YGConfig.h
HEADERS += 3rdparty/yoga/YGEnums.h
HEADERS += 3rdparty/yoga/YGFloatOptional.h
HEADERS += 3rdparty/yoga/YGLayout.h
HEADERS += 3rdparty/yoga/YGMacros.h
HEADERS += 3rdparty/yoga/YGNode.h
HEADERS += 3rdparty/yoga/YGNodePrint.h
HEADERS += 3rdparty/yoga/YGStyle.h
HEADERS += 3rdparty/yoga/YGValue.h
HEADERS += 3rdparty/yoga/Yoga-internal.h
HEADERS += 3rdparty/yoga/Yoga.h
HEADERS +=
HEADERS += 3rdparty/yoga/instrumentation.h
HEADERS +=
HEADERS +=
HEADERS += 3rdparty/dtl/Diff.hpp
HEADERS += 3rdparty/dtl/Diff3.hpp
HEADERS += 3rdparty/dtl/Lcs.hpp
HEADERS += 3rdparty/dtl/Sequence.hpp
HEADERS += 3rdparty/dtl/Ses.hpp
HEADERS += 3rdparty/dtl/dtl.hpp
HEADERS += 3rdparty/dtl/functors.hpp
HEADERS += 3rdparty/dtl/variables.hpp

RESOURCES += res.qrc
