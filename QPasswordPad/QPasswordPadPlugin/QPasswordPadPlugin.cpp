#include "QPasswordPadPlugin.h"
#include "QPasswordPad.h"

#include <QtPlugin>

QPasswordPadPlugin::QPasswordPadPlugin(QObject *parent) :
    QObject(parent),
    mInitialized(false)
{
}

void QPasswordPadPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (mInitialized)
        return;

    mInitialized = true;
}

bool QPasswordPadPlugin::isInitialized() const
{
    return mInitialized;
}

QWidget *QPasswordPadPlugin::createWidget(QWidget *parent)
{
    return new QPasswordPad(parent);
}

QString QPasswordPadPlugin::name() const
{
    return QLatin1String("QPasswordPad");
}

QString QPasswordPadPlugin::group() const
{
    return QLatin1String("Lorenzo Aldrighetti");
}

QIcon QPasswordPadPlugin::icon() const
{
    return QIcon(QLatin1String(":/QPasswordPadPlugin/QPasswordPadPlugin.png"));
}

QString QPasswordPadPlugin::toolTip() const
{
    return QLatin1String("A Pad used to type a password. Can manage different levels of users");
}

QString QPasswordPadPlugin::whatsThis() const
{
    return QLatin1String("A Pad used to type a password");
}

bool QPasswordPadPlugin::isContainer() const
{
    return false;
}

QString QPasswordPadPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QPasswordPad\" name=\"passwordPad\">\n</widget>\n");
}

QString QPasswordPadPlugin::includeFile() const
{
    return QLatin1String("QPasswordPad.h");
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qlightstateindicatorplugin, QLightStateIndicatorPlugin)
#endif // QT_VERSION < 0x050000
