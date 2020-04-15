#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QDeviceState;
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void stateChanged(const bool state);

private slots:
    void setState(const bool state);

private:
    QDeviceState *mDeviceState;
    QDeviceState *mDeviceStateUnlayered;

    QLabel* stateLabel;

    bool mState;
};
