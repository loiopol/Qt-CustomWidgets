#pragma once

#include <QDialog>
#include <QToolButton>

class Button : public QToolButton
{
    Q_OBJECT
public:
    explicit Button(const QString &text, QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

QT_BEGIN_NAMESPACE
class QLineEdit;
class QGridLayout;
class QValidator;
QT_END_NAMESPACE

class QNumericPad : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(NumericPadType numericPadType READ numericPadType WRITE setNumericPadType)
public:
    enum NumericPadType {
        Number,
        OnlyInt
    };
    Q_ENUMS(NumericPadType)
    explicit QNumericPad(QWidget *parent = nullptr);
    explicit QNumericPad(const NumericPadType type, QWidget *parent = nullptr);
    explicit QNumericPad(const double value, QWidget *parent = nullptr);
    explicit QNumericPad(const int value, QWidget *parent = nullptr);

    void value(int &value);
    void value(double &value);
    double getValue() const;

    NumericPadType numericPadType() const;
    void setNumericPadType(const NumericPadType type);

    void setValidator(const double buttom, const double top, const int decimals = 0);
    void setValidator(const int buttom, const int top);
    void setValidator(const QString& regExp);

private slots:
    void connectValidatorSignal();
    void checkInput();

    void digitClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void additiveOperatorClicked();
    void equalClicked();

    void okClicked();
    void cancelClicked();

protected:
    void showEvent(QShowEvent* event);

private:
    void initGui();
    void initGuiDisplay();
    void initGuiButtons();
    void initGuiLayout();

    Button* createButton(const QString &text, const char *member);

    void forceNumericPadType();

    void calculate(double rightOperand, const QString &pendingOperator);

private:
    NumericPadType mType;

    QGridLayout *mainLayout;

    QLineEdit *mDisplay;
    QFont mDisplayFont;
    QPalette mDisplayPalette;
    QPalette mDisplayPaletteError;
    Button *mDigitButtons[10];
    Button *pointButton;
    Button *changeSignButton;
    Button *backspaceButton;
    Button *clearButton;
    Button *minusButton;
    Button *plusButton;
    Button *equalButton;
    Button *okButton;
    Button *cancelButton;

    QValidator *mValidator;

    bool mWaitingForOperand;
    QString pendingAdditiveOperator;
    double sumSoFar;

    double mReturnValue;
};
