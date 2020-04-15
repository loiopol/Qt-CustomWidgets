#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QToolButton;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class QDeviceState : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName READ deviceName WRITE setDeviceName)
    Q_PROPERTY(QString disableButtonText READ disableButtonText WRITE setDisableButtonText)
    Q_PROPERTY(QString enableButtonText READ enableButtonText WRITE setEnableButtonText)
    Q_PROPERTY(bool state READ state WRITE setState)
public:
    explicit QDeviceState(QWidget *parent = nullptr);
    explicit QDeviceState(const QString &label, const QString &disableButtonText, const QString &enableButtonText, QWidget *parent = nullptr);
    ~QDeviceState();

    QSize sizeHint() const override;

    QString deviceName() const;
    void setDeviceName(const QString &deviceName);

    QString disableButtonText() const;
    void setDisableButtonText(const QString &text);

    QString enableButtonText() const;
    void setEnableButtonText(const QString &text);

    bool state() const;

signals:
    void enableButtonClicked();
    void disableButtonClicked();

public slots:
    void setState(const bool state);

private:
    void placeWidgets();
    void initConnections();
    void closeConnections();

    void forceState();

private:
    QToolButton* mIcon;
    QLabel* mLabel;
    QPushButton* mDisableButton;
    QPushButton* mEnableButton;

    bool mState;
};

