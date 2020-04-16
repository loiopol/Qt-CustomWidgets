#pragma once

#include <QMainWindow>

class QPasswordPad;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openPassPad();

private:
    QPasswordPad* mPassPad;
    QLabel *doorStateLabel;
    QPalette normalPalette;
    QPalette errorPalette;
};
