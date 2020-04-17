#include "QPasswordPad.h"

#include <QGridLayout>
#include <QLineEdit>

#include <QApplication>
#include <QPropertyAnimation>

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

QPasswordPad::QPasswordPad(QWidget *parent) :
    QDialog(parent),
    mainLayout(new QGridLayout(this)),
    mDisplay(new QLineEdit("", this)),
    mPasswords(QVector<QString>{""}),
    mReturnValue(-1)
{
    initGui();
}

QPasswordPad::QPasswordPad(const QString &password, QWidget *parent) :
    QDialog(parent),
    mainLayout(new QGridLayout(this)),
    mDisplay(new QLineEdit("", this)),
    mPasswords(QVector<QString>{password}),
    mReturnValue(-1)
{
    initGui();
}

QPasswordPad::QPasswordPad(const QVector<QString> &passwords, QWidget *parent) :
    QDialog(parent),
    mainLayout(new QGridLayout(this)),
    mDisplay(new QLineEdit("", this)),
    mPasswords(passwords),
    mReturnValue(-1)
{
    initGui();
}

void QPasswordPad::setPassword(const QString &pass)
{
    mPasswords = { pass };
}

void QPasswordPad::setPasswords(const QVector<QString> &pass)
{
    mPasswords = pass;
}

void QPasswordPad::addPassword(const QString &pass)
{
    for(const QString &password : mPasswords) {
        if(password == pass)
            return;
    }

    mPasswords.append(pass);
}

void QPasswordPad::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (mDisplay->text() == "0" && digitValue == 0)
        return;

    mDisplay->setText(mDisplay->text() + QString::number(digitValue));
}

void QPasswordPad::backspaceClicked()
{
    QString text = mDisplay->text();
    text.chop(1);
    if (text.isEmpty())
        text = "";

    mDisplay->setText(text);
}

void QPasswordPad::clear()
{
    mDisplay->setText("");
}

void QPasswordPad::okClicked()
{
    QString text = mDisplay->text();

    for (int i = 0; i < mPasswords.size(); i++) {
        if(mPasswords.at(i) == text) {
            mReturnValue = i;
            break;
        }
    }

    done(mReturnValue);
}

void QPasswordPad::cancelClicked()
{
    done(-2);
}

void QPasswordPad::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    QPropertyAnimation* fadeIn = new QPropertyAnimation(this, "windowOpacity");
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setDuration(100);

    fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
}

void QPasswordPad::initGui()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setStyleSheet("QDialog { border: 1px solid grey }");

    initGuiDisplay();
    initGuiButtons();
    initGuiLayout();
}

void QPasswordPad::initGuiDisplay()
{
    mDisplay->setEchoMode(QLineEdit::Password);
    mDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mDisplay->setAlignment(Qt::AlignCenter);
    mDisplay->setMaxLength(15);

    mDisplay->setMinimumSize(50, 50);
    mDisplayFont = mDisplay->font();
    mDisplayFont.setPointSize(mDisplayFont.pointSize() + 5);

    mDisplay->setFont(mDisplayFont);
}

void QPasswordPad::initGuiButtons()
{
    for (int i = 0; i < 10; ++i)
        mDigitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));

    backspaceButton = createButton(tr("\302\253‬"), SLOT(backspaceClicked()));
    backspaceButton->setShortcut(Qt::Key_Backspace);

    clearButton = createButton(tr("Clear"), SLOT(clear()));
    clearButton->setShortcut(Qt::Key_Delete);

    okButton = createButton(tr("Ok"), SLOT(okClicked()));
    okButton->setShortcut(Qt::Key_Return | Qt::Key_Enter);

    cancelButton = createButton(tr("Cancel"), SLOT(cancelClicked()));
    cancelButton->setShortcut(Qt::Key_Escape);

    QPalette okButtonPalette = QApplication::palette();
    okButtonPalette.setColor(QPalette::Button, QColor(41, 128, 185));
    okButton->setPalette(okButtonPalette);

    QPalette cancelButtonPalette = QApplication::palette();
    cancelButtonPalette.setColor(QPalette::Button, QColor(192, 57, 43));
    cancelButton->setPalette(cancelButtonPalette);
}

void QPasswordPad::initGuiLayout()
{
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setMargin(12);

    mainLayout->addWidget(mDisplay, 0, 0, 1, 4);

    for (int i = 1; i < 10; ++i) {
        int row = ((9 - i) / 3) + 1;
        int column = ((i - 1) % 3);
        mainLayout->addWidget(mDigitButtons[i], row, column);
    }

    mainLayout->addWidget(mDigitButtons[0], 4, 0, 1, 3);

    mainLayout->addWidget(backspaceButton, 1, 3, 2, 1);
    mainLayout->addWidget(clearButton, 3, 3, 2, 1);

    mainLayout->addWidget(cancelButton, 5, 0, 1, 2);
    mainLayout->addWidget(okButton, 5, 2, 1, 2);

    setLayout(mainLayout);
}

Button *QPasswordPad::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text, this);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
