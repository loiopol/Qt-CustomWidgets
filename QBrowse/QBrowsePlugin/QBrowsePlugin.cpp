#include "QBrowsePlugin.h"

#include "QBrowse.h"

QBrowseClass::QBrowseClass(QObject *parent) :
    QObject(parent),
    mInitialized(false)
{  
}

QString QBrowseClass::name() const
{
    return QStringLiteral("QBrowse");
}

QString QBrowseClass::group() const
{
    return QStringLiteral("Lorenzo Aldrighetti");
}

QIcon QBrowseClass::icon() const
{
    return QIcon(":/icon.png");
}

QString QBrowseClass::includeFile() const
{
    return QStringLiteral("QBrowse.h");
}

bool QBrowseClass::isContainer() const
{
    return false;
}

bool QBrowseClass::isInitialized() const
{
    return mInitialized;
}

void QBrowseClass::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);

    if (mInitialized)
        return;

    mInitialized = true;
}

QString QBrowseClass::toolTip() const
{
    return QStringLiteral("Widget that help the user in searching for file or folder");
}

QString QBrowseClass::whatsThis() const
{
    return QStringLiteral("Widget that help the user in searching for file or folder");
}

QWidget *QBrowseClass::createWidget(QWidget *parent)
{
    return new QBrowse(parent);
}

QString QBrowseClass::domXml() const
{
    return QStringLiteral("<ui language=\"c++\">\n"
                          " <widget class=\"QBrowse\" name=\"pathBrowser\">\n"
                          "  <property name=\"geometry\">\n"
                          "   <rect>\n"
                          "    <x>0</x>\n"
                          "    <y>0</y>\n"
                          "    <width>300</width>\n"
                          "    <height>22</height>\n"
                          "   </rect>\n"
                          "  </property>\n"
                          " </widget>\n"
                          "</ui>\n");
}
