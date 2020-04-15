#include "MainWindow.h"

#include <QVBoxLayout>
#include <QLabel>

#include "QDeviceState.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mState(false)
{
    resize(400, 220);
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout(this);
    centralWidget()->setLayout(layout);

    QLabel* title = new QLabel(tr("QDeviceState\nBy Lorenzo"), this);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    mDeviceState = new QDeviceState(tr("A general device"), tr("Disconnect"), tr("Connect"), this);
    mDeviceStateUnlayered = new QDeviceState(tr("A new general device"), tr("Disable"), tr("Enable"), this);

    connect(this, &MainWindow::stateChanged, mDeviceState, &QDeviceState::setState);
    connect(this, &MainWindow::stateChanged, mDeviceStateUnlayered, &QDeviceState::setState);

    connect(mDeviceState, &QDeviceState::enableButtonClicked, [this](){ setState(true); });
    connect(mDeviceState, &QDeviceState::disableButtonClicked, [this](){ setState(false); });
    connect(mDeviceStateUnlayered, &QDeviceState::enableButtonClicked, [this](){ setState(true); });
    connect(mDeviceStateUnlayered, &QDeviceState::disableButtonClicked, [this](){ setState(false); });

    stateLabel = new QLabel("State: -", this);
    stateLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QLabel* unlayeredTitle = new QLabel(tr("Unlayered widget"), this);

    layout->addWidget(title);
    layout->addWidget(mDeviceState);
    layout->addWidget(stateLabel);
    layout->addStretch();

    int offset = 120;
    unlayeredTitle->move(5, offset);
    mDeviceStateUnlayered->move(0, offset + 30);
}

MainWindow::~MainWindow()
{
    //! I can avoid to delete the data poinited by pointers. They are all child of the main window
}

void MainWindow::setState(const bool state)
{
    if(mState == state)
        return;

    mState = state;
    stateLabel->setText(tr("State: %1").arg(mState ? "true" : "false"));
    emit stateChanged(mState);
}

