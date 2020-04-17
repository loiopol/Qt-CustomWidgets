#include "MainWindow.h"

#include "QNumericPad.h"

#include <QApplication>
#include <QStyleFactory>

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    resize(300, 260);
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout(this);
    centralWidget()->setLayout(layout);

    QLabel* title = new QLabel(tr("QNumericPad\nBy Lorenzo"), this);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    intSpinBox = new QSpinBox(this);
    intSpinBox->setValue(10);

    openIntNumPad = new QPushButton("Click to change the value", this);
    openIntNumPad->setObjectName("intPushButton");
    connect(openIntNumPad, &QPushButton::clicked, this, &MainWindow::openPad);

    doubleSpinBox = new QDoubleSpinBox(this);
    doubleSpinBox->setValue(33.42);

    openDoubleNumPad = new QPushButton("Click to change the value", this);
    openDoubleNumPad->setObjectName("doublePushButton");
    connect(openDoubleNumPad, &QPushButton::clicked, this, &MainWindow::openPad);

    valueEntered = new QLabel("Operation result", this);
    valueEntered->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    valueEntered->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    layout->addWidget(title);
    layout->addWidget(intSpinBox);
    layout->addWidget(openIntNumPad);
    layout->addWidget(doubleSpinBox);
    layout->addWidget(openDoubleNumPad);
    layout->addWidget(valueEntered);
}

MainWindow::~MainWindow()
{
}


void MainWindow::openPad()
{
    QPushButton *button = qobject_cast<QPushButton* >(sender());

    if(button->objectName() == "intPushButton") {
        mNumPad = new QNumericPad(intSpinBox->value(), this);
        mNumPad->setValidator(intSpinBox->minimum(), intSpinBox->maximum());
    }
    else if(button->objectName() == "doublePushButton") {
        mNumPad = new QNumericPad(doubleSpinBox->value(), this);
        mNumPad->setValidator(doubleSpinBox->minimum(), doubleSpinBox->maximum(), 2);
    }
    else
        return;

    int accepted = mNumPad->exec();
    if(accepted == -1)
        valueEntered->setText("Operation aborted");
    else if(accepted == 0)
        valueEntered->setText("Operation negated. The value selected is not in the range");
    else if(accepted == 1) {
        valueEntered->setText("Operation completed!");
        if(button->objectName() == "intPushButton")
            intSpinBox->setValue(mNumPad->getValue());
        else if(button->objectName() == "doublePushButton")
            doubleSpinBox->setValue(mNumPad->getValue());
    }

    delete mNumPad;
}
