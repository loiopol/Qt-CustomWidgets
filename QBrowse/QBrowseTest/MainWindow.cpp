#include "MainWindow.h"

#include <QVBoxLayout>
#include <QLabel>

#include "QBrowse.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(500, 220);
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout(this);
    centralWidget()->setLayout(layout);

    QLabel* title = new QLabel(tr("QBrowse\nBy Lorenzo"), this);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    mBrowse = new QBrowse(this);
    mBrowseUnlayered = new QBrowse("Please give me the path\nof the map of Treasure", this);

    QLabel* unlayeredTitle = new QLabel(tr("Unlayered widget"), this);

    layout->addWidget(title);
    layout->addWidget(mBrowse);
    layout->addStretch();

    int offset = 120;
    unlayeredTitle->move(5, offset);
    mBrowseUnlayered->move(0, offset + 30);
}

MainWindow::~MainWindow()
{
}

