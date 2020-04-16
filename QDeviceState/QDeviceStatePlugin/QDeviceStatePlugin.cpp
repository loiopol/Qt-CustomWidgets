#include "QDeviceStatePlugin.h"

#include "QDeviceState.h"

QDeviceStatePlugin::QDeviceStatePlugin(QObject *parent)
    : QObject(parent),
      mInitialized(false)
{
}

QString QDeviceStatePlugin::name() const
{
    return QStringLiteral("QDeviceState");
}

QString QDeviceStatePlugin::group() const
{
    return QStringLiteral("Lorenzo Aldrighetti");
}

QIcon QDeviceStatePlugin::icon() const
{
    return QIcon(":/QDeviceStatePlugin/QDeviceStatePlugin.png");
}

QString QDeviceStatePlugin::includeFile() const
{
    return QStringLiteral("QDeviceState.h");
}

bool QDeviceStatePlugin::isContainer() const
{
    return false;
}

bool QDeviceStatePlugin::isInitialized() const
{
    return mInitialized;
}

void QDeviceStatePlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);

    if (mInitialized)
        return;

    mInitialized = true;
}

QString QDeviceStatePlugin::toolTip() const
{
    return QStringLiteral("Display the device state and allow the basics operations on it");
}

QString QDeviceStatePlugin::whatsThis() const
{
    return QStringLiteral("Device state");
}

QWidget *QDeviceStatePlugin::createWidget(QWidget *parent)
{
    return new QDeviceState(parent);
}

QString QDeviceStatePlugin::domXml() const
{
    return QLatin1String("<widget class=\"QDeviceState\" name=\"deviceState\">\n</widget>\n");
}
