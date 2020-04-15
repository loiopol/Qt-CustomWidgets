#pragma once

#include <QWidget>

class QSwitchKnob : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    explicit QSwitchKnob(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    QColor color() const;
    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor mColor;
};

//*----------------------------------------------------------------------------------------*//

class QSwitchSlider : public QWidget
{
    Q_OBJECT
public:
    explicit QSwitchSlider(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
};

//*----------------------------------------------------------------------------------------*//

class QGraphicsDropShadowEffect;
class QParallelAnimationGroup;

class QSwitchIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit QSwitchIndicator(const bool isActive, const bool fullSize, QWidget *parent = nullptr);
    ~QSwitchIndicator();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    int maximumBarWidth() const;
    void setMaximumBarWidth(const int width);

    bool fullSize();
    void setFullSize(const bool fullSize);

    QColor onColor() const;
    void setOnColor(const QColor& color);

    bool isActive() const;
    void setActive(const bool active);

    int margins() const;

signals:
    void triggered(const bool isActive);

protected:
    void mousePressEvent(QMouseEvent *event) override;

#ifdef PRINT_FRAME
    void paintEvent(QPaintEvent *event) override;
#endif
    void resizeEvent(QResizeEvent *event) override;

private:
    void computeKnobPos();
    void animateWidgets();

private:
    QSwitchSlider* mSlider;
    QSwitchKnob* mKnob;
    QGraphicsDropShadowEffect* shadowEffect;
    QParallelAnimationGroup *mAnimations;

    int mMargins;
    int mMaximumBarWidth;

    bool mIsActive;
    QPoint mKnobStartPos;
    QPoint mKnobEndPos;
    QColor mOnColor;
    QColor mOffColor;

    int mAnimationTime;
};


//*----------------------------------------------------------------------------------------*//

class QHBoxLayout;
class QLabel;

class QSwitch : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool isActive READ isActive WRITE setActive NOTIFY triggered)
    Q_PROPERTY(bool labelsVisible READ labelsVisible WRITE setLabelsVisible)
    Q_PROPERTY(int maximumBarWidth READ maximumBarWidth WRITE setMaximumBarWidth)
    Q_PROPERTY(bool fullSize READ fullSize WRITE setFullSize)
    Q_PROPERTY(QString offText READ offText WRITE setOffText)
    Q_PROPERTY(QString onText READ onText WRITE setOnText)
    Q_PROPERTY(QColor onColor READ onColor WRITE setOnColor)
public:
    explicit QSwitch(QWidget *parent = nullptr);
    explicit QSwitch(const bool isActive, QWidget *parent = nullptr);
    explicit QSwitch(const bool isActive, const bool showLabels, QWidget *parent = nullptr);
    explicit QSwitch(const bool isActive, const bool showLabels, const bool slideBarFullWidth, QWidget *parent = nullptr);
    ~QSwitch();

    QSize sizeHint() const override;

    bool isActive() const;
    void setActive(const bool active);

    bool labelsVisible() const;
    void setLabelsVisible(const bool visible);

    int maximumBarWidth() const;
    void setMaximumBarWidth(const int maxLength);

    bool fullSize() const;
    void setFullSize(const bool setEqual);

    QString offText() const;
    void setOffText(const QString& offText);

    QString onText() const;
    void setOnText(const QString& onText);

    QColor onColor() const;
    void setOnColor(const QColor& color);

#ifdef PRINT_FRAME
protected:
    void paintEvent(QPaintEvent *event) override;
#endif

signals:
    void triggered(const bool active);

private:
    void init();
    void placeWidgets();
    void forceLabelsVisible();

private:
    QHBoxLayout *mLayout;
    QLabel *mOffLabel;
    QSwitchIndicator* mSwitchIndicator;
    QLabel *mOnLabel;

    bool mLabelsVisible;
};
