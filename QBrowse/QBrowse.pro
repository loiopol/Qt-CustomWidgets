TEMPLATE = subdirs

DISTFILES += \
    QBrowse.cpp \
    QBrowse.h \
    QBrowse.pri \
    resource.qrc \

#QT += widgets uiplugin
#CONFIG += plugin
#CONFIG += c++14
#TEMPLATE = lib

#TARGET = $$qtLibraryTarget($$TARGET)
#INSTALLS += target
#windows {
#    target.path = $$(QT_DIR)/../../Tools/QtCreator/bin/plugins/designer

#    debug:target_lib.files = $$OUT_PWD/debug/$${TARGET}.lib
#    release:target_lib.files = $$OUT_PWD/release/$${TARGET}.lib
#    target_lib.path = $$(QT_DIR)/../../Tools/QtCreator/bin/plugins/designer
#    INSTALLS += target_lib
#}

#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}

#INSTALLS    += target_lib


#RESOURCES += \
#    QBrowse.qrc

#HEADERS += \
#    ../QSwitch/QSwitch.h \
#    QBrowsePlugin.h

#SOURCES += \
#    ../QSwitch/QSwitch.cpp \
#    QBrowsePlugin.cpp

#include(QBrowse.pri)

SUBDIRS += \
    QBrowsePlugin \
    QBrowseTest
