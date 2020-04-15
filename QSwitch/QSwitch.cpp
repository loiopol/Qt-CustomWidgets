#include "QSwitch.h"

#include <QPainter>
#include <QPropertyAnimation>

QSwitchKnob::QSwitchKnob(QWidget *parent) :
    QWidget(parent)
{
    QPalette palette;
    mColor = palette.color(QPalette::Disabled, QPalette::ButtonText).lighter(160);
    resize(20, 20);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize QSwitchKnob::minimumSizeHint() const
{
    return QSize(20, 20);
}

QSize QSwitchKnob::sizeHint() const
{
    return QSize(20, 20);
}

QColor QSwitchKnob::color() const
{
    return mColor;
}

void QSwitchKnob::setColor(const QColor& color)
{
    mColor = color;
    update();
}

void QSwitchKnob::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
#ifdef PRINT_FRAME
    painter.drawRect(0, 0, width(), height());
#endif
    painter.setPen(Qt::NoPen);
    QColor brushColor = mColor;
    brushColor.setAlpha(isEnabled() ? 255 : 218);
    painter.setBrush(QBrush(brushColor.darker(isEnabled() ? 100 : 137), Qt::SolidPattern));
    painter.drawEllipse(rect());
}

//*----------------------------------------------------------------------------------------*//
//*----------------------------------------------------------------------------------------*//
//*----------------------------------------------------------------------------------------*//

QSwitchSlider::QSwitchSlider(QWidget *parent) :
    QWidget(parent)
{
    resize(28, 6);
}

QSize QSwitchSlider::minimumSizeHint() const
{
    return QSize(28, 6);
}

QSize QSwitchSlider::sizeHint() const
{
    return QSize(28, 6);
}

void QSwitchSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPalette palette;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
#ifdef PRINT_FRAME
    painter.drawRect(0, 0, width(), height());
#endif
    painter.setPen(Qt::NoPen);

    QPainterPath slider;
    slider.addRoundedRect(QRectF(0, 0, width(), height()), height()/2, height()/2);
    QColor brushColor = palette.color(QPalette::Disabled, QPalette::ButtonText);
    brushColor.setAlpha(isEnabled() ? 255 : 200);
    painter.fillPath(slider, brushColor);
}

//*----------------------------------------------------------------------------------------*//
//*----------------------------------------------------------------------------------------*//
//*----------------------------------------------------------------------------------------*//

#include <QParallelAnimationGroup>
#include <QGraphicsDropShadowEffect>

QSwitchIndicator::QSwitchIndicator(const bool isActive, const bool fullSize, QWidget *parent) :
    QWidget(parent),
    mSlider(new QSwitchSlider(this)),
    mKnob(new QSwitchKnob(this)),
    shadowEffect(new QGraphicsDropShadowEffect(this)),
    mAnimations(new QParallelAnimationGroup(this)),
    mMargins(2),
    mMaximumBarWidth(40),
    mIsActive(isActive),
    mKnobStartPos(),
    mKnobEndPos(),
    mOffColor(),
    mOnColor(QColor(62, 219, 73)),
    mAnimationTime(350)
{
    shadowEffect->setOffset(0);
    shadowEffect->setBlurRadius(3);
    mKnob->setGraphicsEffect(shadowEffect);
    resize(28 + mMargins*2, 20 + mMargins*2);

    QPalette palette;
    mOffColor =  palette.color(QPalette::Disabled, QPalette::ButtonText).lighter(160);
    if(!mIsActive)
        mKnob->setColor(mOffColor);
    else
        mKnob->setColor(mOnColor);

    if(fullSize)
        mSlider->resize(mSlider->width(), mKnob->height());
}

QSwitchIndicator::~QSwitchIndicator()
{
    delete shadowEffect;
    delete mAnimations;
    delete mKnob;
    delete mSlider;
}

QSize QSwitchIndicator::minimumSizeHint() const
{
    return QSize(28 + mMargins*2, 20 + mMargins*2);
}

QSize QSwitchIndicator::sizeHint() const
{
//    return QSize(mSlider->width() + mMargins*2, 20 + mMargins*2);
    return QSize(mMaximumBarWidth + mMargins*2, 20 + mMargins*2);
}

int QSwitchIndicator::maximumBarWidth() const
{
    return mMaximumBarWidth;
}

void QSwitchIndicator::setMaximumBarWidth(const int width)
{
    if(mMaximumBarWidth == width)
        return;

    mMaximumBarWidth = width;
    adjustSize();
    updateGeometry();
//    resizeEvent(nullptr);
}

bool QSwitchIndicator::fullSize()
{
    return mKnob->height() == mSlider->height();
}

void QSwitchIndicator::setFullSize(const bool fullSize)
{
    if((fullSize && this->fullSize()) || (!fullSize && !this->fullSize()))
        return;

    if(fullSize)
        mSlider->resize(mSlider->width(), mKnob->height());
    else
        mSlider->resize(mSlider->width(), 6);
    resizeEvent(nullptr);
}

QColor QSwitchIndicator::onColor() const
{
    return mOnColor;
}

void QSwitchIndicator::setOnColor(const QColor &color)
{
    if(mOnColor == color)
        return;

    mOnColor = color;
    animateWidgets();
}

bool QSwitchIndicator::isActive() const
{
    return mIsActive;
}

void QSwitchIndicator::setActive(const bool active)
{
    if(mIsActive == active)
        return;

    mIsActive = active;
    animateWidgets();
}

int QSwitchIndicator::margins() const
{
    return mMargins;
}

void QSwitchIndicator::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if(!isEnabled())
        return;
    emit triggered(mIsActive);
    setActive(!mIsActive);
}

#ifdef PRINT_FRAME
void QSwitchIndicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRect(0, 0, width(), height());
}
#endif

void QSwitchIndicator::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    int barWidth = width() - mMargins*2;
    if(barWidth > mMaximumBarWidth)
        barWidth = mMaximumBarWidth;

    mSlider->setGeometry((width() - mSlider->width())/2, (height() - mSlider->height())/2, barWidth, mSlider->height());
    mSlider->move((width() - mSlider->width())/2, (height() - mSlider->height())/2 );

    computeKnobPos();
    if(!mIsActive)
        mKnob->move(mKnobStartPos);
    else
        mKnob->move(mKnobEndPos);
}

void QSwitchIndicator::computeKnobPos()
{
    mKnobStartPos = QPoint(mSlider->x()                                    , mSlider->y() + mSlider->height()/2 - mKnob->height()/2);
    mKnobEndPos   = QPoint(mSlider->x() + mSlider->width() - mKnob->width(), mSlider->y() + mSlider->height()/2 - mKnob->height()/2);
}

void QSwitchIndicator::animateWidgets()
{
    mAnimations->clear();

    auto knobPosAnim = new QPropertyAnimation(mKnob, "pos");
    knobPosAnim->setDuration(mAnimationTime);
    QPoint asd = mKnob->pos();
    knobPosAnim->setStartValue(mKnob->pos());
    knobPosAnim->setEasingCurve(QEasingCurve::OutQuint);
    if(!mIsActive)
        knobPosAnim->setEndValue(mKnobStartPos);
    else
        knobPosAnim->setEndValue(mKnobEndPos);
    mAnimations->addAnimation(knobPosAnim);

    auto knobColorAnim = new QPropertyAnimation(mKnob, "color");
    knobColorAnim->setDuration(mAnimationTime);
    knobColorAnim->setStartValue(mKnob->color());
    knobColorAnim->setEasingCurve(QEasingCurve::OutQuint);
    if(!mIsActive)
        knobColorAnim->setEndValue(mOffColor);
        else
        knobColorAnim->setEndValue(mOnColor);
    mAnimations->addAnimation(knobColorAnim);

    mAnimations->start();
}

//*----------------------------------------------------------------------------------------*//
//*----------------------------------------------------------------------------------------*//
//*----------------------------------------------------------------------------------------*//

#include <QHBoxLayout>
#include <QLabel>

QSwitch::QSwitch(QWidget *parent) :
    QWidget(parent),
    mLayout(new QHBoxLayout(this)),
    mOffLabel(new QLabel("OFF", this)),
    mSwitchIndicator(new QSwitchIndicator(false, false, this)),
    mOnLabel(new QLabel("ON", this)),
    mLabelsVisible(true)
{
    init();
}

QSwitch::QSwitch(const bool isActive, QWidget *parent) :
    QWidget(parent),
    mLayout(new QHBoxLayout(this)),
    mOffLabel(new QLabel("OFF", this)),
    mSwitchIndicator(new QSwitchIndicator(isActive, false, this)),
    mOnLabel(new QLabel("ON", this)),
    mLabelsVisible(true)
{
    init();
}

QSwitch::QSwitch(const bool isActive, const bool showLabels, QWidget *parent) :
    QWidget(parent),
    mLayout(new QHBoxLayout(this)),
    mOffLabel(new QLabel("OFF", this)),
    mSwitchIndicator(new QSwitchIndicator(isActive, false, this)),
    mOnLabel(new QLabel("ON", this)),
    mLabelsVisible(showLabels)
{
    init();
}

QSwitch::QSwitch(const bool isActive, const bool showLabels, const bool slideBarFullWidth, QWidget *parent) :
    QWidget(parent),
    mLayout(new QHBoxLayout(this)),
    mOffLabel(new QLabel("OFF", this)),
    mSwitchIndicator(new QSwitchIndicator(isActive, slideBarFullWidth, this)),
    mOnLabel(new QLabel("ON", this)),
    mLabelsVisible(showLabels)
{
    init();
}

QSwitch::~QSwitch()
{
    delete mOffLabel;
    delete mOnLabel;
    delete mSwitchIndicator;
    delete mLayout;
}

QSize QSwitch::sizeHint() const
{
    int width = 0;
    int heigth = 0;
    if(mLabelsVisible) {
        QFontMetrics fm(mOffLabel->font());
        QSize sz = fm.size(Qt::TextShowMnemonic, mOffLabel->text());
        width += sz.width();
        if(heigth < sz.height())
            heigth = sz.height();

        sz = fm.size(Qt::TextShowMnemonic, mOnLabel->text());
        width += sz.width();
        if(heigth < sz.height())
            heigth = sz.height();
    }

    width += mSwitchIndicator->width() < 28 ? 28 : mSwitchIndicator->width();
    int switchHeigth = 20 + mSwitchIndicator->margins()*2;
    if(heigth < switchHeigth)
        heigth = switchHeigth;

    width += mLayout->spacing() * (mLabelsVisible ? 4 : 2);

    QMargins margins = mLayout->contentsMargins();
    width += margins.left() + margins.right();
    heigth += margins.top() + margins.bottom();

    return QSize(width, heigth);
}

bool QSwitch::labelsVisible() const
{
    return mLabelsVisible;
}

void QSwitch::setLabelsVisible(const bool visible)
{
    if(mLabelsVisible == visible)
        return;

    mLabelsVisible = visible;
    forceLabelsVisible();
}

bool QSwitch::isActive() const
{
    return mSwitchIndicator->isActive();
}

void QSwitch::setActive(const bool active)
{
    mSwitchIndicator->setActive(active);
}

int QSwitch::maximumBarWidth() const
{
    return mSwitchIndicator->maximumBarWidth();
}

void QSwitch::setMaximumBarWidth(const int maxWidth)
{
    mSwitchIndicator->setMaximumBarWidth(maxWidth);
}

bool QSwitch::fullSize() const
{
    return mSwitchIndicator->fullSize();
}

void QSwitch::setFullSize(const bool setEqual)
{
    mSwitchIndicator->setFullSize(setEqual);
}

QString QSwitch::offText() const
{
    return mOffLabel->text();
}

void QSwitch::setOffText(const QString &offText)
{
    if(mOffLabel->text() == offText)
        return;

    mOffLabel->setText(offText);
    adjustSize();
    updateGeometry();
}

QString QSwitch::onText() const
{
    return mOnLabel->text();
}

void QSwitch::setOnText(const QString &onText)
{
    if(mOnLabel->text() == onText)
        return;

    mOnLabel->setText(onText);
    adjustSize();
    updateGeometry();
}

QColor QSwitch::onColor() const
{
    return mSwitchIndicator->onColor();
}

void QSwitch::setOnColor(const QColor &color)
{
    mSwitchIndicator->setOnColor(color);
}

#ifdef PRINT_FRAME
void QSwitch::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRect(0, 0, width(), height());
}
#endif

void QSwitch::init()
{
    connect(mSwitchIndicator, &QSwitchIndicator::triggered, this, &QSwitch::triggered);
    placeWidgets();
    forceLabelsVisible();
}

void QSwitch::placeWidgets()
{
    mOffLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    mOffLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    mSwitchIndicator->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    mOnLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    mOnLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    mLayout->setSpacing(2);
    mLayout->setContentsMargins(5, 2, 5, 2);
    mLayout->addWidget(mOffLabel);
    mLayout->addWidget(mSwitchIndicator);
    mLayout->addWidget(mOnLabel);

    setLayout(mLayout);
}

void QSwitch::forceLabelsVisible()
{
    mOffLabel->setVisible(mLabelsVisible);
    mOnLabel->setVisible(mLabelsVisible);
    adjustSize();
    updateGeometry();
}
