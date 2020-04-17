#include "QNumericPad.h"

#include <QGridLayout>
#include <QLineEdit>

#include <QApplication>
#include <QPropertyAnimation>
#include <QValidator>

Button::Button(const QString &text, QWidget *parent) :
    QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}

QSize Button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 30;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

QNumericPad::QNumericPad(QWidget *parent) :
    QDialog(parent),
    mType(Number),
    mainLayout(new QGridLayout(this)),
    mDisplay(new QLineEdit("", this)),
    mValidator(nullptr),
    mWaitingForOperand(false),
    pendingAdditiveOperator(""),
    sumSoFar(0.0),
    mReturnValue(0.0)
{
    initGui();
}

QNumericPad::QNumericPad(const QNumericPad::NumericPadType type, QWidget *parent) :
    QDialog(parent),
    mType(type),
    mainLayout(new QGridLayout(this)),
    mDisplay(new QLineEdit("", this)),
    mValidator(nullptr),
    mWaitingForOperand(false),
    pendingAdditiveOperator(""),
    sumSoFar(0.0),
    mReturnValue(0.0)
{
    initGui();
}

QNumericPad::QNumericPad(const double value, QWidget *parent) :
    QDialog(parent),
    mType(Number),
    mainLayout(new QGridLayout(this)),
    mDisplay(new QLineEdit(QString::number(value, 'f'), this)),
    mValidator(nullptr),
    mWaitingForOperand(false),
    pendingAdditiveOperator(""),
    sumSoFar(0.0),
    mReturnValue(0.0)
{
    initGui();
    mDisplay->selectAll();
}

QNumericPad::QNumericPad(const int value, QWidget *parent) :
    QDialog(parent),
    mType(OnlyInt),
    mainLayout(new QGridLayout(this)),
    mDisplay(new QLineEdit(QString::number(value), this)),
    mValidator(nullptr),
    mWaitingForOperand(false),
    pendingAdditiveOperator(""),
    sumSoFar(0.0),
    mReturnValue(0.0)
{
    initGui();
    mDisplay->selectAll();
    forceNumericPadType();
}

void QNumericPad::value(int &value)
{
    value = static_cast<int>(mReturnValue);
}

void QNumericPad::value(double &value)
{
    value = mReturnValue;
}

double QNumericPad::getValue() const
{
    return mReturnValue;
}

QNumericPad::NumericPadType QNumericPad::numericPadType() const
{
    return mType;
}

void QNumericPad::setNumericPadType(const QNumericPad::NumericPadType type)
{
    if(mType == type)
        return;

    mType = type;
    forceNumericPadType();
}

void QNumericPad::setValidator(const double buttom, const double top, const int decimals)
{
    if(buttom > top)
        return;

    connectValidatorSignal();
    mValidator = new QDoubleValidator(buttom, top, decimals);
    mDisplay->setValidator(mValidator);
    mDisplay->setText(QString::number(mDisplay->text().toDouble(), 'f', decimals));

    mDisplay->selectAll();
}

void QNumericPad::setValidator(const int buttom, const int top)
{
    if(buttom > top)
        return;

    connectValidatorSignal();
    mValidator = new QIntValidator(buttom, top);
    mDisplay->setValidator(mValidator);
    mDisplay->setText(QString::number(mDisplay->text().toInt()));

    mDisplay->selectAll();
}

void QNumericPad::setValidator(const QString &regExp)
{
    connectValidatorSignal();
    mValidator = new QRegExpValidator(QRegExp(regExp));
    mDisplay->setValidator(mValidator);
}

void QNumericPad::connectValidatorSignal()
{
    if(mValidator != nullptr)
        return;

    connect(mDisplay, &QLineEdit::cursorPositionChanged, this, &QNumericPad::checkInput);
}

void QNumericPad::checkInput()
{
    okButton->setEnabled(mDisplay->hasAcceptableInput());
    if(mDisplay->hasAcceptableInput())
        mDisplay->setPalette(mDisplayPalette);
    else
        mDisplay->setPalette(mDisplayPaletteError);
}

void QNumericPad::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (mDisplay->text() == "0" && digitValue == 0)
        return;

    if (mWaitingForOperand) {
        mDisplay->clear();
        mWaitingForOperand = false;
    }

    if(mDisplay->selectionLength() > 0)
        mDisplay->clear();

    mDisplay->setText(mDisplay->text() + QString::number(digitValue));
}

void QNumericPad::pointClicked()
{
    if (mWaitingForOperand)
        mDisplay->setText("0");
    if (!mDisplay->text().contains('.'))
        mDisplay->setText(mDisplay->text() + tr("."));

    mWaitingForOperand = false;
}

void QNumericPad::changeSignClicked()
{
    QString text = mDisplay->text();
    double value = text.toDouble();

    if (value > 0.0)
        text.prepend(tr("-"));
    else if (value < 0.0)
        text.remove(0, 1);

    mDisplay->setText(text);
}

void QNumericPad::backspaceClicked()
{
    if (mWaitingForOperand)
        return;

    QString text = mDisplay->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "";
        mWaitingForOperand = true;
    }

    mDisplay->setText(text);
}

void QNumericPad::clear()
{
    sumSoFar = 0.0;
    mWaitingForOperand = true;
    mDisplay->setText("");
}

void QNumericPad::additiveOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = mDisplay->text().toDouble();

    if (!pendingAdditiveOperator.isEmpty()) {
        calculate(operand, pendingAdditiveOperator);
        mDisplay->setText(QString::number(sumSoFar));
    }
    else
        sumSoFar = operand;

    pendingAdditiveOperator = clickedOperator;
    mWaitingForOperand = true;
}

void QNumericPad::equalClicked()
{
    double operand = mDisplay->text().toDouble();

    if (!pendingAdditiveOperator.isEmpty()) {
        calculate(operand, pendingAdditiveOperator);
        pendingAdditiveOperator.clear();
    }
    else
        sumSoFar = operand;


    mDisplay->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    mWaitingForOperand = true;
}

void QNumericPad::okClicked()
{
    if(mDisplay->text() == "") {
        reject();
        return;
    }

    QString finalValue = mDisplay->text();
    int pos = 0;
    if(mValidator != nullptr && mValidator->validate(finalValue, pos) != QValidator::Acceptable) {
        reject();
        return;
    }

    switch (mType) {
    case Number:
        mReturnValue = mDisplay->text().toDouble();
        accept();
        break;
    case OnlyInt:
        mReturnValue = mDisplay->text().toInt();
        accept();
        break;
    }
}

void QNumericPad::cancelClicked()
{
    done(-1);
}

void QNumericPad::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    QPropertyAnimation* fadeAnim = new QPropertyAnimation(this, "windowOpacity");
    fadeAnim->setStartValue(0.0);
    fadeAnim->setEndValue(1.0);
    fadeAnim->setDuration(100);

    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

void QNumericPad::initGui()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setStyleSheet("QDialog { border: 1px solid grey }");

    initGuiDisplay();
    initGuiButtons();
    initGuiLayout();
}

void QNumericPad::initGuiDisplay()
{
    mDisplay->setReadOnly(true);
    mDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mDisplay->setAlignment(Qt::AlignCenter);
    mDisplay->setMaxLength(15);

    mDisplay->setMinimumSize(50, 50);
    mDisplayFont = mDisplay->font();
    mDisplayFont.setPointSize(mDisplayFont.pointSize() + 5);

    mDisplayPaletteError = mDisplayPalette = mDisplay->palette();
    mDisplayPaletteError.setColor(QPalette::Text, QColor(192, 57, 43));

    mDisplay->setFont(mDisplayFont);
}

void QNumericPad::initGuiButtons()
{
    for (int i = 0; i < 10; ++i) {
        mDigitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
        mDigitButtons[i]->setShortcut(Qt::Key_0 + i);
    }

    pointButton = createButton(tr("."), SLOT(pointClicked()));
    if(mType == NumericPadType::Number)
        pointButton->setShortcut(Qt::Key_Period);

    changeSignButton = createButton(tr("\302\261"), SLOT(changeSignClicked()));

    backspaceButton = createButton(tr("\302\253‬"), SLOT(backspaceClicked()));
    backspaceButton->setShortcut(Qt::Key_Backspace);

    clearButton = createButton(tr("Clear"), SLOT(clear()));
    clearButton->setShortcut(Qt::Key_Delete);

    minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    minusButton->setShortcut(Qt::Key_Minus);

    plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));
    plusButton->setShortcut(Qt::Key_Plus);

    equalButton = createButton(tr("="), SLOT(equalClicked()));
    equalButton->setShortcut(Qt::Key_Enter);

    okButton = createButton(tr("Ok"), SLOT(okClicked()));
    okButton->setShortcut(Qt::Key_Return);

    cancelButton = createButton(tr("Cancel"), SLOT(cancelClicked()));
    cancelButton->setShortcut(Qt::Key_Escape);

    QPalette okButtonPalette = QApplication::palette();
    okButtonPalette.setColor(QPalette::Button, QColor(41, 128, 185));
    okButton->setPalette(okButtonPalette);

    QPalette cancelButtonPalette = QApplication::palette();
    cancelButtonPalette.setColor(QPalette::Button, QColor(192, 57, 43));
    cancelButton->setPalette(cancelButtonPalette);
}

void QNumericPad::initGuiLayout()
{
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setMargin(10);

    mainLayout->addWidget(mDisplay, 0, 0, 1, 3);
    mainLayout->addWidget(backspaceButton, 0, 3);

    for (int i = 1; i < 10; ++i) {
        int row = ((9 - i) / 3) + 1;
        int column = ((i - 1) % 3);
        mainLayout->addWidget(mDigitButtons[i], row, column);
    }

    mainLayout->addWidget(mDigitButtons[0], 4, 0);
    mainLayout->addWidget(pointButton, 4, 1);
    mainLayout->addWidget(changeSignButton, 4, 2);

    mainLayout->addWidget(minusButton, 1, 3);
    mainLayout->addWidget(plusButton, 2, 3);
    mainLayout->addWidget(clearButton, 3, 3);
    mainLayout->addWidget(equalButton, 4, 3);

    mainLayout->addWidget(cancelButton, 5, 0, 1, 1);
    mainLayout->addWidget(okButton, 5, 1, 1, 3);

    setLayout(mainLayout);
}

Button *QNumericPad::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text, this);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void QNumericPad::forceNumericPadType()
{
    pointButton->setEnabled(mType == Number);
}

void QNumericPad::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+"))
        sumSoFar += rightOperand;
    else if (pendingOperator == tr("-"))
        sumSoFar -= rightOperand;
}
