#pragma once

#include <QMainWindow>

class QNumericPad;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openPad();

private:
    QNumericPad* mNumPad;
    QSpinBox *intSpinBox;
    QPushButton* openIntNumPad;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton* openDoubleNumPad;

    QLabel *valueEntered;
};
