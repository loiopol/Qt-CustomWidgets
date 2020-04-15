TEMPLATE = subdirs

SUBDIRS += \
    QLedIndicatorPlugin \
    QLedIndicatorPlugin \
    QLedIndicatorTest \
    QLedIndicatorTest

DISTFILES += \
    QLedIndicator.cpp \
    QLedIndicator.h \
    QLedIndicator.pri \
    led.svg \
    led_green.png \
    led_grey.png \
    led_orange.png \
    led_red.png \

RESOURCES += \
    QLedIndicator.qrc
