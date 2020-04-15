#include "QLedIndicator.h"
#include "QLedIndicatorPlugin.h"

#include <QtPlugin>

QLedIndicatorPlugin::QLedIndicatorPlugin(QObject *parent)
    : QObject(parent)
{
    mInitialized = false;
}

void QLedIndicatorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (mInitialized)
        return;

    mInitialized = true;
}

bool QLedIndicatorPlugin::isInitialized() const
{
    return mInitialized;
}

QWidget *QLedIndicatorPlugin::createWidget(QWidget *parent)
{
    return new QLedIndicator(parent);
}

QString QLedIndicatorPlugin::name() const
{
    return QLatin1String("QLedIndicator");
}

QString QLedIndicatorPlugin::group() const
{
    return QLatin1String("Lorenzo Aldrighetti");
}

QIcon QLedIndicatorPlugin::icon() const
{
    return QIcon(QLatin1String(":/icon.png"));
}

QString QLedIndicatorPlugin::toolTip() const
{
    return QLatin1String("Led that display a color wrt a state plus a label");
}

QString QLedIndicatorPlugin::whatsThis() const
{
    return QLatin1String("Led that display a color given 4 possible state. You can also place a text label");
}

bool QLedIndicatorPlugin::isContainer() const
{
    return false;
}

QString QLedIndicatorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QLedIndicator\" name=\"ledIndicator\">\n</widget>\n");
}

QString QLedIndicatorPlugin::includeFile() const
{
    return QLatin1String("QLedIndicator.h");
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qlightstateindicatorplugin, QLightStateIndicatorPlugin)
#endif // QT_VERSION < 0x050000
