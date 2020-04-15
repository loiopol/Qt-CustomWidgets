#include "QDeviceMultiState.h"

#include <QHBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>

QDeviceMultiState::QDeviceMultiState(QWidget *parent) :
    QWidget(parent),
    mIcon(new QToolButton(this)),
    mLabel(new QLabel(tr("Device state"), this)),
    mDisableButton(new QPushButton(tr("Disable"), this)),
    mEnableButton(new QPushButton(tr("Enable"), this)),
    mTriggerButton(new QPushButton(tr("Trigger"), this)),
    mState(State::CrossError)
{
    placeWidgets();
    initConnections();
    forceState();
}

QDeviceMultiState::QDeviceMultiState(const QString &label, const QString &disableButtonText, const QString &enableButtonText, const QString &triggerButtonText, QWidget *parent) :
    QWidget(parent),
    mIcon(new QToolButton(this)),
    mLabel(new QLabel(label, this)),
    mDisableButton(new QPushButton(disableButtonText, this)),
    mEnableButton(new QPushButton(enableButtonText, this)),
    mTriggerButton(new QPushButton(triggerButtonText, this)),
    mState(State::CrossError)
{
    placeWidgets();
    initConnections();
    forceState();
}

QDeviceMultiState::~QDeviceMultiState()
{
    closeConnections();

    delete mIcon;
    delete mLabel;
    delete mDisableButton;
    delete mEnableButton;
    delete mTriggerButton;
}

QSize QDeviceMultiState::sizeHint() const
{
    int width = 0;
    QFontMetrics fm(mLabel->font());
    QSize sz = fm.size(Qt::TextShowMnemonic, mLabel->text());
    width += sz.width();

    width += 20;
    width += mDisableButton->width();
    width += mEnableButton->width();
    width += mTriggerButton->width();

    return QSize(width, mDisableButton->height());
}

QString QDeviceMultiState::deviceName() const
{
    return mLabel->text();
}

void QDeviceMultiState::setDeviceName(const QString &deviceName)
{
    if(mLabel->text() == deviceName)
        return;

    mLabel->setText(deviceName);
}

QString QDeviceMultiState::disableButtonText() const
{
    return mDisableButton->text();
}

void QDeviceMultiState::setDisableButtonText(const QString &text)
{
    if(mDisableButton->text() == text)
        return;
    mDisableButton->setText(text);
}

QString QDeviceMultiState::enableButtonText() const
{
    return mEnableButton->text();
}

void QDeviceMultiState::setEnableButtonText(const QString &text)
{
    if(mEnableButton->text() == text)
        return;
    mEnableButton->setText(text);
}

QString QDeviceMultiState::triggerButtonText() const
{
    return mTriggerButton->text();
}

void QDeviceMultiState::setTriggerButtonText(const QString &text)
{
    if(mTriggerButton->text() == text)
        return;

    mTriggerButton->setText(text);
}

QDeviceMultiState::State QDeviceMultiState::state() const
{
    return mState;
}

void QDeviceMultiState::setState(const int state)
{
    setState(static_cast<State>(state));
}

void QDeviceMultiState::setState(const QDeviceMultiState::State state)
{
    if(mState == state)
        return;

    mState = state;
    forceState();
}

void QDeviceMultiState::placeWidgets()
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);

    mIcon->setAutoRaise(true);
    setState(mState);

    layout->addWidget(mIcon);
    layout->addWidget(mLabel);
    layout->addStretch();
    layout->addWidget(mTriggerButton);
    layout->addWidget(mDisableButton);
    layout->addWidget(mEnableButton);

    setLayout(layout);

    adjustSize();
}

void QDeviceMultiState::initConnections()
{
    connect(mDisableButton, &QPushButton::clicked, this, &QDeviceMultiState::disableButtonClicked);
    connect(mEnableButton, &QPushButton::clicked, this, &QDeviceMultiState::enableButtonClicked);
    connect(mTriggerButton, &QPushButton::clicked, this, &QDeviceMultiState::triggerButtonClicked);

    connect(this, &QDeviceMultiState::stateChanged, this, &QDeviceMultiState::setButtonsState);
}

void QDeviceMultiState::closeConnections()
{
    disconnect(mDisableButton, &QPushButton::clicked, this, &QDeviceMultiState::disableButtonClicked);
    disconnect(mEnableButton, &QPushButton::clicked, this, &QDeviceMultiState::enableButtonClicked);
    disconnect(mTriggerButton, &QPushButton::clicked, this, &QDeviceMultiState::triggerButtonClicked);

    disconnect(this, &QDeviceMultiState::stateChanged, this, &QDeviceMultiState::setButtonsState);
}

void QDeviceMultiState::forceState()
{
    switch (mState) {
    case State::Tick:
        mIcon->setIcon(QIcon(":/QDeviceMultiState/tick_green.svg"));
        break;
    case State::TickWarning:
        mIcon->setIcon(QIcon(":/QDeviceMultiState/tick_yellow.svg"));
        break;
    case State::CrossError:
        mIcon->setIcon(QIcon(":/QDeviceMultiState/cross_red.svg"));
        break;
    case State::CrossWarning:
        mIcon->setIcon(QIcon(":/QDeviceMultiState/cross_yellow.svg"));
        break;
    default:
        return;
    }

    emit stateChanged();
}

void QDeviceMultiState::setButtonsState()
{
    switch (mState) {
    case State::Tick:
        mEnableButton->setEnabled(false);
        mDisableButton->setEnabled(true);
        mTriggerButton->setEnabled(true);
        break;
    case State::TickWarning:
        mEnableButton->setEnabled(false);
        mDisableButton->setEnabled(true);
        mTriggerButton->setEnabled(true);
        break;
    case State::CrossWarning:
        mEnableButton->setEnabled(false);
        mDisableButton->setEnabled(true);
        mTriggerButton->setEnabled(false);
        break;
    case State::CrossError:
        mEnableButton->setEnabled(true);
        mDisableButton->setEnabled(false);
        mTriggerButton->setEnabled(false);
        break;
    }
}
