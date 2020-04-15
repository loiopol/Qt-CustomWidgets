#pragma once

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class QBrowseClass : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
#endif // QT_VERSION >= 0x050000

public:
    explicit QBrowseClass(QObject *parent = nullptr);

    QString name() const;
    QString group() const;
    QIcon icon() const;
    QString includeFile() const;

    bool isContainer() const;
    bool isInitialized() const;
    void initialize(QDesignerFormEditorInterface *core);
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    QString domXml() const;

private:
    bool mInitialized;
};

