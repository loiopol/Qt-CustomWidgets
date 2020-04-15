#include "MainWindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "QDeviceMultiState.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      invalidateButton(new QPushButton("Invalidate Device", this)),
      generateErrorButton(new QPushButton("Generate an error to the Device", this)),
      mState(QDeviceMultiState::CrossError),
      mTrigCount(0)
{
    resize(450, 250);
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout(this);
    centralWidget()->setLayout(layout);

    QLabel* title = new QLabel(tr("QDeviceState\nBy Lorenzo"), this);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    mDeviceState = new QDeviceMultiState(tr("A general device"), tr("Disconnect"), tr("Connect"), tr("Trigger State"), this);
    mDeviceStateUnlayered = new QDeviceMultiState(tr("A new general device"), tr("Disable"), tr("Enable"), tr("Trigger State"), this);

    connect(this, &MainWindow::stateChanged, mDeviceState, QOverload<const int>::of(&QDeviceMultiState::setState));
    connect(this, &MainWindow::stateChanged, mDeviceStateUnlayered, QOverload<const int>::of(&QDeviceMultiState::setState));

    connect(mDeviceState, &QDeviceMultiState::enableButtonClicked, [this](){ setState(QDeviceMultiState::Tick); });
    connect(mDeviceState, &QDeviceMultiState::disableButtonClicked, [this](){ setState(QDeviceMultiState::CrossError); });
    connect(mDeviceState, &QDeviceMultiState::triggerButtonClicked, this, &MainWindow::setTriggerCount);
    connect(mDeviceStateUnlayered, &QDeviceMultiState::enableButtonClicked, [this](){ setState(QDeviceMultiState::Tick); });
    connect(mDeviceStateUnlayered, &QDeviceMultiState::disableButtonClicked, [this](){ setState(QDeviceMultiState::CrossError); });
    connect(mDeviceStateUnlayered, &QDeviceMultiState::triggerButtonClicked, this, &MainWindow::setTriggerCount);

    connect(invalidateButton, &QPushButton::clicked, [this](){ setState(QDeviceMultiState::TickWarning); });
    connect(generateErrorButton, &QPushButton::clicked, [this](){ setState(QDeviceMultiState::CrossWarning); });

    stateLabel = new QLabel("State: -", this);
    stateLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    triggerCountLabel = new QLabel(tr("Trigger count: -"), this);
    triggerCountLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QLabel* unlayeredTitle = new QLabel(tr("Unlayered widget"), this);

    layout->addWidget(title);
    layout->addWidget(mDeviceState);
    layout->addWidget(stateLabel);
    layout->addWidget(triggerCountLabel);
    layout->addWidget(invalidateButton);
    layout->addWidget(generateErrorButton);
    layout->addStretch();

    int offset = 170;
    unlayeredTitle->move(5, offset);
    mDeviceStateUnlayered->move(0, offset + 30);
}

MainWindow::~MainWindow()
{
    //! I can avoid to delete the data poinited by pointers. They are all child of the main window
}

void MainWindow::setState(const int state)
{
    if(mState == state)
        return;

    mState = state;
    QString stateText;
    switch (mState) {
    case QDeviceMultiState::Tick:
        stateText = "Enabled";
        break;
    case QDeviceMultiState::TickWarning:
        stateText = "Enabled but require attention";
        break;
    case QDeviceMultiState::CrossWarning:
        stateText = "Disabled due to an error";
        break;
    case QDeviceMultiState::CrossError:
        stateText = "Disabled";
        break;
    }
    stateLabel->setText(tr("State: %1").arg(stateText));
    emit stateChanged(mState);
}

void MainWindow::setTriggerCount()
{
    triggerCountLabel->setText(tr("Trigger count: %1").arg(++mTrigCount));
}

