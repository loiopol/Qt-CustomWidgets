# Qt Custom Widgets #

A collection of Qt widgets created over time, for my work and my hobbies.

## Widget structure ##

Each widget was developer following the structure below:

- ***QWidgetNamePlugin***: Inside this folder there are the rules for deploying the widget for Qt Creator.
    - *QWidgetNamePlugin.cpp*
    - *QWidgetNamePlugin.h*
    - *icons.qrc*
    - *icon.png* (64x64 px)
- ***QWidgetNameTest***: Inside this folder there are a simple application window in which I tested the layout and the settings of the widget in a layout and not.
    - *main.cpp*
    - *MainWindow.cpp*
    - *MainWindow.h*
- *QWidgetName.cpp*: The core of the widget.
- *QWidgetName.h*: The core of the widget.
- *QWidgetName.qrc*: Optional, only if the widget use images or audio elements.
- *QWidgetName.pri*: The progect file for inclusion of the widget.

## Include my widgets in your project ##

There are two practicals way for including a/some/all widgets in your project:

### Including each .pri in your .pro ###

The simplest solution is to add the respective project file for inclusion *.pri* of the desired widget that you want to include, in your *.pro* file using the command:
```
include(path/to/folder/QWidgetName.pri)
```

### Including the main .pri and specify the widgets ###

If you prefer to use this collection as a library. I promise its development and maintainability over time.
For first specify the list of the widgets that you want to include in your project using the command *CONFIG*. The convention used is **USE_CW_*****WIDGETNAME*** (note that the *Q* before *WidgetName* is missing)
After simply include the main *.pri* file *CustomWidgets.pri* located in the repository root folder, in your *.pro* file.

An example is reported below

```
CONFIG += USE_CW_BROWSE USE_CW_FORMLABEL USE_CW_SWITCH
include(path/to/root/repository/CustomWidgets.pri)
```

## Credit ##
Developer: [Lorenzo Aldrighetti](https://linkedin.com/in/lorenzo-aldrighetti)

Enjoy!
