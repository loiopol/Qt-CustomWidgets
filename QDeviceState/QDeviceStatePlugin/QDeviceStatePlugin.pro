CONFIG += plugin debug_and_release
TEMPLATE = lib

LIBS += -L.

#If defined, display the frame of each widget
CONFIG(debug, debug|release) : DEFINES += PRINT_FRAME

TARGET = $$qtLibraryTarget($$TARGET)
INSTALLS += target
windows {
    target.path = $$(QT_DIR)/../../Tools/QtCreator/bin/plugins/designer

    debug:target_lib.files = $$OUT_PWD/debug/$${TARGET}.lib
    release:target_lib.files = $$OUT_PWD/release/$${TARGET}.lib
    target_lib.path = $$(QT_DIR)/../../Tools/QtCreator/bin/plugins/designer
    INSTALLS += target_lib
}

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

HEADERS += \
    QDeviceStatePlugin.h

SOURCES += \
    QDeviceStatePlugin.cpp

include(../QDeviceState.pri)

RESOURCES += \
    icons.qrc
