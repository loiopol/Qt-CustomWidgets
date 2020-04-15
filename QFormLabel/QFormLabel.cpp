#include "QFormLabel.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QClipboard>

QFormLabel::QFormLabel(QWidget *parent) :
    QWidget(parent),
    mLayout(new QHBoxLayout(this)),
    mText("Label"),
    mValueSeparator(Colon),
    mLabelText(new QLabel("Label: ", this)),
    mLabelValue(new QLabel("-", this)),
    mValue("-"),
    mLabelUnit(new QLabel("", this)),
    mUnit(""),
    mTextAlignment(TextAlignment::Left)
{
    setupUi();
    forceTextAlignment();
}

QFormLabel::QFormLabel(const QString &text, const QString &unit, QWidget *parent) :
    QWidget(parent),
    mLayout(new QHBoxLayout(this)),
    mText(text),
    mValueSeparator(Colon),
    mLabelText(new QLabel(mText + ":", this)),
    mLabelValue(new QLabel("-", this)),
    mValue("-"),
    mLabelUnit(new QLabel("", this)),
    mUnit(unit),
    mTextAlignment(TextAlignment::Left)
{

}

QFormLabel::~QFormLabel()
{
    delete mLabelText;
    delete mLabelValue;
    delete mLabelUnit;

    delete mLayout;
}

QSize QFormLabel::minimumSizeHint() const
{
    int width = 0, height = 0;
    QFontMetrics fm(mLabelText->font());
    QSize sz = fm.size(Qt::TextShowMnemonic, mText + getValueSeparator());
    width += sz.width();
    height += sz.height();

    sz = fm.size(Qt::TextShowMnemonic, mLabelValue->text());
    width += sz.width();

    if(mUnit != "") {
        sz = fm.size(Qt::TextShowMnemonic, mLabelUnit->text() + "[]");
        width += sz.width();
    }

    width += 3*4;
    height += 3*2;

    return QSize(width, height);
}

QSize QFormLabel::sizeHint() const
{
    int width = 0, height = 0;
    QFontMetrics fm(mLabelText->font());
    QSize sz = fm.size(Qt::TextShowMnemonic, mText + getValueSeparator());
    width += sz.width();
    height += sz.height();

    sz = fm.size(Qt::TextShowMnemonic, mLabelValue->text());
    width += sz.width();

    if(mUnit != "") {
        sz = fm.size(Qt::TextShowMnemonic, mLabelUnit->text() + "[]");
        width += sz.width();
    }

    width += 3*5;
    height += 3*2;

    return QSize(width, height);
}

QString QFormLabel::text() const
{
    return mText;
}

void QFormLabel::setText(const QString &text)
{
    if(mText == text)
        return;

    mText = text;
    mLabelText->setText(mText + getValueSeparator());

    adjustSize();
}

QString QFormLabel::value() const
{
    return mLabelValue->text();
}

void QFormLabel::setValue(const QString &value)
{
    if(mLabelValue->text() == value)
        return;

    mLabelValue->setText(value);

    adjustSize();
}

void QFormLabel::setValue(const int value)
{
    setValue(QString::number(value));
}

void QFormLabel::setValue(const double value, const int decimals)
{
    setValue(QString::number(value, 'f', decimals));
}

QFormLabel::ValueSeparator QFormLabel::valueSeparator() const
{
    return mValueSeparator;
}

void QFormLabel::setValueSeparator(const QFormLabel::ValueSeparator valueSeparator)
{
    if(mValueSeparator == valueSeparator)
        return;

    mValueSeparator = valueSeparator;
    setText(mText);
}

QString QFormLabel::unit() const
{
    return mUnit;
}

QFormLabel::TextAlignment QFormLabel::textAlignment() const
{
    return mTextAlignment;
}

void QFormLabel::setUnit(const QString &unit)
{
    if(mUnit == unit)
        return;

    mUnit = unit;
    forceTextAlignment();
    if(mUnit == "") {
        mLabelUnit->setVisible(false);
        return;
    }

    mLabelUnit->setVisible(true);
    mLabelUnit->setText(" [" + mUnit + "]");

    adjustSize();
}

void QFormLabel::setTextAlignment(const QFormLabel::TextAlignment textAlignment)
{
    if(mTextAlignment == textAlignment)
        return;

    mTextAlignment = textAlignment;
    forceTextAlignment();
}

void QFormLabel::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(mLabelValue->text());
}

void QFormLabel::setupUi()
{
    mLayout->setMargin(3);

    mLabelText->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    mLabelUnit->setVisible(false);

    mLayout->addWidget(mLabelText);
    mLayout->addWidget(mLabelValue);
    mLayout->addWidget(mLabelUnit);

    setLayout(mLayout);

    adjustSize();
}

QString QFormLabel::getValueSeparator() const
{
    switch (mValueSeparator) {
    case None:
        return "";
    case Colon:
        return ":";
    case Hyphen:
        return " ->";
    default:
        return "";
    }
}

void QFormLabel::forceTextAlignment()
{
    switch (mTextAlignment) {
    case Left:
        mLabelValue->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        mLabelUnit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        mLabelText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        mLabelValue->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        mLabelValue->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        break;
    case Center:
        if(mUnit == "")
            mLabelValue->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        else
            mLabelValue->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        mLabelUnit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        mLabelText->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        mLabelValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        mLabelValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        break;
    }
}
