#include "QDeviceMultiStatePlugin.h"

#include "QDeviceMultiState.h"

QDeviceStatePlugin::QDeviceStatePlugin(QObject *parent)
    : QObject(parent),
      mInitialized(false)
{
}

QString QDeviceStatePlugin::name() const
{
    return QStringLiteral("QDeviceMultiState");
}

QString QDeviceStatePlugin::group() const
{
    return QStringLiteral("Lorenzo Aldrighetti");
}

QIcon QDeviceStatePlugin::icon() const
{
    return QIcon(":/icon.png");
}

QString QDeviceStatePlugin::includeFile() const
{
    return QStringLiteral("QDeviceMultiState.h");
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
    return QStringLiteral("Device Multi state");
}

QWidget *QDeviceStatePlugin::createWidget(QWidget *parent)
{
    return new QDeviceMultiState(parent);
}

QString QDeviceStatePlugin::domXml() const
{
    return QLatin1String("<widget class=\"QDeviceMultiState\" name=\"deviceMultiState\">\n</widget>\n");
}
