#include "MainWindow.h"

#include "QPasswordPad.h"

#include <QApplication>
#include <QStyleFactory>

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    resize(300, 260);
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout(this);
    centralWidget()->setLayout(layout);

    QLabel* title = new QLabel(tr("QPasswordPad\nBy Lorenzo"), this);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QPushButton* openDoorButton = new QPushButton("Click for open the door", this);
    connect(openDoorButton, &QPushButton::clicked, this, &MainWindow::openPassPad);

    doorStateLabel = new QLabel("Door is close", this);
    doorStateLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    doorStateLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    errorPalette = normalPalette = doorStateLabel->palette();
    normalPalette.setColor(QPalette::WindowText, Qt::green);;
    errorPalette.setColor(QPalette::WindowText, Qt::red);

    layout->addWidget(title);
    layout->addWidget(openDoorButton);
    layout->addWidget(doorStateLabel);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openPassPad()
{
    mPassPad = new QPasswordPad({"1234", "321", "0000"}, this);
    int result = mPassPad->exec();


    if(result == -1) {
        doorStateLabel->setText("Autentication Failed! The door is still close");
        doorStateLabel->setPalette(errorPalette);
    }
    else if(result >= 0) {
        doorStateLabel->setText(tr("Door open! You are autenticated with the level %1").arg(result));
        doorStateLabel->setPalette(normalPalette);
    }
}

