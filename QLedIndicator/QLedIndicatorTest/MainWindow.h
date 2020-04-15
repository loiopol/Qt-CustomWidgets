#pragma once

#include <QMainWindow>

class QLedIndicator;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLedIndicator *mLed;
    QLedIndicator *mLedUnlayered;
};
