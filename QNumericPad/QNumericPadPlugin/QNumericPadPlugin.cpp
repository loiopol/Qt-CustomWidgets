#include "QNumericPadPlugin.h"
#include "QNumericPad.h"

#include <QtPlugin>

QNumericPadPlugin::QNumericPadPlugin(QObject *parent) :
    QObject(parent),
    mInitialized(false)
{
}

void QNumericPadPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (mInitialized)
        return;

    mInitialized = true;
}

bool QNumericPadPlugin::isInitialized() const
{
    return mInitialized;
}

QWidget *QNumericPadPlugin::createWidget(QWidget *parent)
{
    return new QNumericPad(parent);
}

QString QNumericPadPlugin::name() const
{
    return QLatin1String("QNumericPad");
}

QString QNumericPadPlugin::group() const
{
    return QLatin1String("Lorenzo Aldrighetti");
}

QIcon QNumericPadPlugin::icon() const
{
    return QIcon(QLatin1String(":/QNumericPadPlugin/QNumericPadPugin.png"));
}

QString QNumericPadPlugin::toolTip() const
{
    return QLatin1String("A Pad used to type and compute numbers. A validator can be setted to be sure that the value dont exceed the limits");
}

QString QNumericPadPlugin::whatsThis() const
{
    return QLatin1String("A Pad used to type and compute numbers");
}

bool QNumericPadPlugin::isContainer() const
{
    return false;
}

QString QNumericPadPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QNumericPad\" name=\"numericPad\">\n</widget>\n");
}

QString QNumericPadPlugin::includeFile() const
{
    return QLatin1String("QNumericPad.h");
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qlightstateindicatorplugin, QLightStateIndicatorPlugin)
#endif // QT_VERSION < 0x050000
