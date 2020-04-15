#pragma once

#include <QMainWindow>

class QFormLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QFormLabel *mFormLabel;
    QFormLabel *mFormLabelUnlayered;
};
