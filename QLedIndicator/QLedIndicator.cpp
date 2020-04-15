#include "QLedIndicator.h"

#include <QGridLayout>
#include <QLabel>

QLedIndicator::QLedIndicator(QWidget *parent) :
    QWidget(parent),
    mLayout(new QGridLayout(this)),
    mLed(new QLabel(this)),
    mLabel(new QLabel("Text", this)),
    mLedState(Inactive),
    mLedSize(20),
    mLabelPosition(Bottom),
    mMargins(6)
{
    setupUi();
}

QLedIndicator::QLedIndicator(const QString &text, const QLedIndicator::LabelPosition labelPosition, QWidget *parent) :
    QWidget(parent),
    mLayout(new QGridLayout(this)),
    mLed(new QLabel(this)),
    mLabel(new QLabel(text, this)),
    mLedState(Inactive),
    mLedSize(20),
    mLabelPosition(labelPosition),
    mMargins(6)
{
    setupUi();
}

QSize QLedIndicator::sizeHint() const
{
    int width = 0, height = 0;
    QFontMetrics fm(mLabel->font());
    QSize sz = fm.size(Qt::TextShowMnemonic, mLabel->text());
    switch (mLabelPosition) {
    case Hide:
        width += mLedSize;
        height += mLedSize;
        break;
    case Left:
        width += mLedSize + sz.width() + mLayout->margin();
        height += mLedSize;
        break;
    case Top:
        width += mLedSize > sz.width() ? mLedSize : sz.width();
        height += mLedSize + sz.height() + mLayout->margin();
        break;
    case Right:
        width += mLedSize + sz.width() + mLayout->margin();
        height += mLedSize;
        break;
    case Bottom:
        width += mLedSize > sz.width() ? mLedSize : sz.width();
        height += mLedSize + sz.height() + mLayout->margin();
        break;
    }

    width += mLayout->margin()*2;
    height += mLayout->margin()*2;

    return QSize(width, height);
}

QLedIndicator::LedState QLedIndicator::ledState() const
{
    return mLedState;
}

int QLedIndicator::ledSize() const
{
    return mLedSize;
}

QLedIndicator::LabelPosition QLedIndicator::labelPosition() const
{
    return mLabelPosition;
}

void QLedIndicator::setLabelPosition(const QLedIndicator::LabelPosition position)
{
    if(mLabelPosition == position)
        return;

    mLabelPosition = position;
    forceLabelPosition();
    forceWidgetSize();
}

QString QLedIndicator::text() const
{
    return mLabel->text();
}

int QLedIndicator::margins() const
{
    return mMargins;
}

void QLedIndicator::setMargins(const int margins)
{
    if(mMargins == margins || margins < 7)
        return;

    mMargins = margins;
    forceWidgetSize();
}

void QLedIndicator::setLedState(const LedState state)
{
    if(mLedState == state)
        return;

    mLedState = state;
    forceLedState();
    emit ledStateChanged(mLedState);
    emit ledStateChanged(static_cast<int>(mLedState));
}

void QLedIndicator::setLedState(const int state)
{
    setLedState(static_cast<LedState>(state));
}

void QLedIndicator::setLedSize(const int size)
{
    if(mLedSize == size || size < 15 || size > 64)
        return;

    mLedSize = size;
    forceLedState();
    forceWidgetSize();
}

void QLedIndicator::setText(const QString &text)
{
    if(mLabel->text() == text)
        return;

    mLabel->setText(text);
    forceWidgetSize();
}

void QLedIndicator::setupUi()
{
    initLed();
    initLabel();

    setLayout(mLayout);
    forceWidgetSize();
}

void QLedIndicator::initLed()
{
    mLed->setMargin(0);
    mLayout->addWidget(mLed, 1, 1);

    forceLedState();
}

void QLedIndicator::forceLedState()
{
    QPixmap icon;
    switch (mLedState) {
    case Error:
        icon.load(":/QLedIndicator/led_red.png");
        break;
    case Inactive:
        icon.load(":/QLedIndicator/led_grey.png");
        break;
    case Active:
        icon.load(":/QLedIndicator/led_green.png");
        break;
    case Warning:
        icon.load(":/QLedIndicator/led_orange.png");
        break;
    }

    mLed->setPixmap(icon.scaled(QSize(mLedSize, mLedSize), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void QLedIndicator::initLabel()
{
    mLabel->setMargin(0);
    forceLabelPosition();
}

void QLedIndicator::forceLabelPosition()
{
    mLayout->removeWidget(mLabel);

    switch (mLabelPosition) {
    case Hide:
        mLed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        break;
    case Left:
        mLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        mLayout->addWidget(mLabel, 1, 0);
        break;
    case Top:
        mLed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        mLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
        mLayout->addWidget(mLabel, 0, 1);
        break;
    case Right:
        mLed->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        mLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        mLayout->addWidget(mLabel, 1, 2);
        break;
    case Bottom:
        mLed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        mLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        mLayout->addWidget(mLabel, 2, 1);
        break;
    }

    mLabel->setVisible(mLabelPosition != Hide);

    adjustSize();
    updateGeometry();
}

void QLedIndicator::forceWidgetSize()
{
    int textWidth = mLabelPosition == Hide ? 0 : mLabel->sizeHint().width();

    switch (mLabelPosition) {
    case Hide:
        setMinimumSize(QSize(mLedSize + mMargins, mLedSize + mMargins));
    case Left:
    case Right:
        setMinimumSize(QSize(mLedSize + textWidth + 3*mMargins, mLedSize + 2*mMargins));
        break;
    case Top:
    case Bottom:
        setMinimumSize(QSize((textWidth < mLedSize ? mLedSize : textWidth ) + 3*mMargins, mLedSize + mLabel->sizeHint().height() + 3*mMargins));
        break;
    }
}
