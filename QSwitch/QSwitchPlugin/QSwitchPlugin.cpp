#include "QSwitch.h"
#include "QSwitchPlugin.h"

QSwitchPlugin::QSwitchPlugin(QObject *parent)
    : QObject(parent)
{
    mInitialized = false;
}

QString QSwitchPlugin::name() const
{
    return QStringLiteral("QSwitch");
}

QString QSwitchPlugin::group() const
{
    return QStringLiteral("Lorenzo Aldrighetti");
}

QIcon QSwitchPlugin::icon() const
{
    return QIcon(":/icon.png");
}

QString QSwitchPlugin::includeFile() const
{
    return QStringLiteral("QSwitch.h");
}

bool QSwitchPlugin::isContainer() const
{
    return false;
}

bool QSwitchPlugin::isInitialized() const
{
    return mInitialized;
}

void QSwitchPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);
    if (mInitialized)
        return;

    mInitialized = true;
}

QString QSwitchPlugin::toolTip() const
{
    return QStringLiteral("Simple switch with two states");
}

QString QSwitchPlugin::whatsThis() const
{
    return QStringLiteral("Simple switch with two states and a label for each status");
}

QWidget *QSwitchPlugin::createWidget(QWidget *parent)
{
    return new QSwitch(false, true, true, parent);
}

QString QSwitchPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QSwitch\" name=\"switch\">\n</widget>\n");
}
