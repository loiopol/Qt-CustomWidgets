#include "QFormLabelPlugin.h"

#include "QFormLabel.h"

QFormLabelPlugin::QFormLabelPlugin(QObject *parent) :
    QObject(parent),
    mInitialized(false)
{

}

QString QFormLabelPlugin::name() const
{
    return QStringLiteral("QFormLabel");
}

QString QFormLabelPlugin::group() const
{
    return QStringLiteral("Lorenzo Aldrighetti");
}

QString QFormLabelPlugin::toolTip() const
{
    return QStringLiteral("Item description and value");
}

QString QFormLabelPlugin::whatsThis() const
{
    return QStringLiteral("Display the current value of the item speficied");
}

QString QFormLabelPlugin::includeFile() const
{
    return QStringLiteral("QFormLabel.h");
}

QIcon QFormLabelPlugin::icon() const
{
    return QIcon(":/icon.png");
}

bool QFormLabelPlugin::isContainer() const
{
    return false;
}

QWidget *QFormLabelPlugin::createWidget(QWidget *parent)
{
    return new QFormLabel(parent);
}

bool QFormLabelPlugin::isInitialized() const
{
    return mInitialized;
}

void QFormLabelPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);
    if (mInitialized)
        return;

    mInitialized = true;
}
