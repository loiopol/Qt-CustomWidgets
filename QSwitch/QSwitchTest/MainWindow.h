#pragma once

#include <QMainWindow>
#include "QSwitch.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setNewKnobColor();

private:
    QSwitch* mSwitch;
    QSwitch* mSwitchNoLabels;
    QSwitch* mUnlayerSwitch;
    QSwitch* mUnlayerSwitchNoLabels;

    QSwitchIndicator* switchObject;
    QSwitchIndicator* unlayeredSwitchObject;
    QSwitchIndicator* unlayeredSwitchObjectOff;
};
