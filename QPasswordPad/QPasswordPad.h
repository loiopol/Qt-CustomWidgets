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
QT_END_NAMESPACE

class QPasswordPad : public QDialog
{
    Q_OBJECT
public:
    explicit QPasswordPad(QWidget *parent = nullptr);
    explicit QPasswordPad(const QString& password, QWidget *parent = nullptr);
    explicit QPasswordPad(const QVector<QString> &passwords, QWidget *parent = nullptr);

    void setPassword(const QString &pass);
    void setPasswords(const QVector<QString> &pass);
    void addPassword(const QString &pass);

private slots:
    void digitClicked();
    void backspaceClicked();
    void clear();

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

private:
    QGridLayout *mainLayout;

    QLineEdit *mDisplay;
    QFont mDisplayFont;
    Button *mDigitButtons[10];
    Button *backspaceButton;
    Button *clearButton;
    Button *okButton;
    Button *cancelButton;

    QVector<QString> mPasswords;
    int mReturnValue;
};
