#pragma once

#include <QWidget>

class QGridLayout;
class QLabel;

class QLedIndicator : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(LedState ledState READ ledState WRITE setLedState NOTIFY ledStateChanged)
    Q_PROPERTY(int ledSize READ ledSize WRITE setLedSize)
    Q_PROPERTY(LabelPosition labelPosition READ labelPosition WRITE setLabelPosition)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(int margins READ margins WRITE setMargins)

public:
    enum LedState { Error = -1, Inactive = 0, Active = 1, Warning = 2 };
    Q_ENUMS(LedState)

    enum LabelPosition { Hide, Left, Top, Right, Bottom };
    Q_ENUMS(LabelPosition)

    QLedIndicator(QWidget *parent = nullptr);
    QLedIndicator(const QString& text, const LabelPosition labelPosition = Bottom, QWidget *parent = nullptr);

    QSize sizeHint() const override;

    LedState ledState() const;
    int ledSize() const;
    LabelPosition labelPosition() const;
    void setLabelPosition(const LabelPosition position);
    QString text() const;
    int margins() const;
    void setMargins(const int margins);

signals:
    void ledStateChanged(const LedState state);
    void ledStateChanged(const int state);

public Q_SLOTS:
    void setLedState(const LedState state);
    void setLedState(const int state);
    void setLedSize(const int size);
    void setText(const QString& text);

private:
    inline void setupUi();
    inline void initLed();
    void forceLedState();
    inline void initLabel();
    void forceLabelPosition();

    void forceWidgetSize();

private:
    QGridLayout *mLayout;
    QLabel* mLed;
    QLabel* mLabel;

    LedState mLedState;
    int mLedSize;
    LabelPosition mLabelPosition;

    int mMargins;
};

