#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QToolButton;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class QDeviceMultiState : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName READ deviceName WRITE setDeviceName)
    Q_PROPERTY(QString disableButtonText READ disableButtonText WRITE setDisableButtonText)
    Q_PROPERTY(QString enableButtonText READ enableButtonText WRITE setEnableButtonText)
    Q_PROPERTY(QString triggerButtonText READ triggerButtonText WRITE setTriggerButtonText)
    Q_PROPERTY(State state READ state WRITE setState)
public:
    enum State {
        Tick,
        TickWarning,
        CrossWarning,
        CrossError
    };
    Q_ENUMS(State)

    explicit QDeviceMultiState(QWidget *parent = nullptr);
    explicit QDeviceMultiState(const QString &label, const QString &disableButtonText, const QString &enableButtonText, const QString &triggerButtonText, QWidget *parent = nullptr);
    ~QDeviceMultiState();

    QSize sizeHint() const override;

    QString deviceName() const;
    void setDeviceName(const QString &deviceName);

    QString disableButtonText() const;
    void setDisableButtonText(const QString &text);

    QString enableButtonText() const;
    void setEnableButtonText(const QString &text);

    QString triggerButtonText() const;
    void setTriggerButtonText(const QString &text);

    State state() const;

signals:
    void disableButtonClicked();
    void enableButtonClicked();
    void triggerButtonClicked();

    void stateChanged();

public slots:
    void setState(const int state);
    void setState(const State state);

private:
    void placeWidgets();
    void initConnections();
    void closeConnections();

    void forceState();
    void setButtonsState();

private:
    QToolButton* mIcon;
    QLabel* mLabel;
    QPushButton* mDisableButton;
    QPushButton* mEnableButton;
    QPushButton* mTriggerButton;

    State mState;
};

