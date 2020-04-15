#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QDeviceMultiState;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void stateChanged(const int state);

private slots:
    void setState(const int state);
    void setTriggerCount();

private:
    QDeviceMultiState *mDeviceState;
    QDeviceMultiState *mDeviceStateUnlayered;

    QLabel* stateLabel;
    QLabel* triggerCountLabel;

    QPushButton *invalidateButton;
    QPushButton *generateErrorButton;

    int mState;
    int mTrigCount;
};
