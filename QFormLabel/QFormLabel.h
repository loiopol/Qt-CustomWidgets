#pragma once

#include <QWidget>

class QLabel;
class QHBoxLayout;

class QFormLabel : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(ValueSeparator valueSeparator READ valueSeparator WRITE setValueSeparator)
    Q_PROPERTY(QString unit READ unit WRITE setUnit)
    Q_PROPERTY(TextAlignment textAlignment READ textAlignment WRITE setTextAlignment)

public:
    enum ValueSeparator { None, Colon, Hyphen };
    Q_ENUMS(ValueSeparator)

    enum TextAlignment { Left, Center };
    Q_ENUMS(TextAlignment)

    explicit QFormLabel(QWidget *parent = nullptr);
    explicit QFormLabel(const QString& text, const QString& unit = "", QWidget *parent = nullptr);
    ~QFormLabel();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    QString text() const;

    QString value() const;

    ValueSeparator valueSeparator() const;

    QString unit() const;

    TextAlignment textAlignment() const;

public Q_SLOT:
    void setText(const QString& text);

    void setValue(const QString& value);
    void setValue(const int value);
    void setValue(const double value, const int decimals);

    void setValueSeparator(const ValueSeparator valueSeparator);

    void setUnit(const QString& unit);

    void setTextAlignment(const TextAlignment textAlignment);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    void setupUi();
    QString getValueSeparator() const;

    void forceTextAlignment();

private:
    QHBoxLayout *mLayout;

    QString mText;
    ValueSeparator mValueSeparator;
    QString mValue;
    QString mUnit;

    QLabel *mLabelText;
    QLabel *mLabelValue;
    QLabel *mLabelUnit;

    TextAlignment mTextAlignment;
};

