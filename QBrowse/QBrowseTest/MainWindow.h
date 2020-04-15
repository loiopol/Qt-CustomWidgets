#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QBrowse;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QBrowse *mBrowse;
    QBrowse *mBrowseUnlayered;
};
