#include "QDeviceState.h"

#include <QHBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>

QDeviceState::QDeviceState(QWidget *parent) :
    QWidget(parent),
    mIcon(new QToolButton(this)),
    mLabel(new QLabel(tr("Device state"), this)),
    mDisableButton(new QPushButton(tr("Disable"), this)),
    mEnableButton(new QPushButton(tr("Enable"), this)),
    mState(false)
{
    placeWidgets();
    initConnections();
    forceState();
}

QDeviceState::QDeviceState(const QString &label, const QString &disableButtonText, const QString &enableButtonText, QWidget *parent) :
    QWidget(parent),
    mIcon(new QToolButton(this)),
    mLabel(new QLabel(label, this)),
    mDisableButton(new QPushButton(disableButtonText, this)),
    mEnableButton(new QPushButton(enableButtonText, this)),
    mState(false)
{
    placeWidgets();
    initConnections();
    forceState();
}

QDeviceState::~QDeviceState()
{
    closeConnections();

    delete mIcon;
    delete mLabel;
    delete mDisableButton;
    delete mEnableButton;
}

QSize QDeviceState::sizeHint() const
{
    int width = 0;
    QFontMetrics fm(mLabel->font());
    QSize sz = fm.size(Qt::TextShowMnemonic, mLabel->text());
    width += sz.width();

    width += 20;
    width += mDisableButton->width();
    width += mEnableButton->width();

    return QSize(width, mDisableButton->height());
}

QString QDeviceState::deviceName() const
{
    return mLabel->text();
}

void QDeviceState::setDeviceName(const QString &deviceName)
{
    if(mLabel->text() == deviceName)
        return;

    mLabel->setText(deviceName);
}

QString QDeviceState::disableButtonText() const
{
    return mDisableButton->text();
}

void QDeviceState::setDisableButtonText(const QString &text)
{
    if(mDisableButton->text() == text)
        return;
    mDisableButton->setText(text);
}

QString QDeviceState::enableButtonText() const
{
    return mEnableButton->text();
}

void QDeviceState::setEnableButtonText(const QString &text)
{
    if(mEnableButton->text() == text)
        return;
    mEnableButton->setText(text);
}

bool QDeviceState::state() const
{
    return mState;
}

void QDeviceState::setState(const bool state)
{
    if(mState == state)
        return;

    mState = state;
    forceState();
}

void QDeviceState::placeWidgets()
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);

    mIcon->setAutoRaise(true);
    setState(mState);

    layout->addWidget(mIcon);
    layout->addWidget(mLabel);
    layout->addStretch();
    layout->addWidget(mDisableButton);
    layout->addWidget(mEnableButton);

    setLayout(layout);

    adjustSize();
}

void QDeviceState::initConnections()
{
    connect(mDisableButton, &QPushButton::clicked, this, &QDeviceState::disableButtonClicked);
    connect(mEnableButton, &QPushButton::clicked, this, &QDeviceState::enableButtonClicked);
}

void QDeviceState::closeConnections()
{
    disconnect(mDisableButton, &QPushButton::clicked, this, &QDeviceState::disableButtonClicked);
    disconnect(mEnableButton, &QPushButton::clicked, this, &QDeviceState::enableButtonClicked);
}

void QDeviceState::forceState()
{
    if(mState)
        mIcon->setIcon(QIcon(":/tick_green.svg"));
    else
        mIcon->setIcon(QIcon(":/cross_red.svg"));

    mDisableButton->setEnabled(mState);
    mEnableButton->setEnabled(!mState);
}
