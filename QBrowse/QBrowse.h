#pragma once

#include <QWidget>

class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class QBrowse : public QWidget
{
    Q_OBJECT


    Q_PROPERTY(BrowserType browserType READ browserType WRITE setBrowserType)
    Q_PROPERTY(bool showDefaultButton READ showDefaultButton WRITE setShowDefaultButton)

    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_PROPERTY(QString placeholder READ placeholder WRITE setPlaceholder)
    Q_PROPERTY(QString buttonText READ buttonText WRITE setButtonText)
    Q_PROPERTY(QString defaultButtonText READ defaultButtonText WRITE setDefaultButtonText)
    Q_PROPERTY(QString defaultPath READ defaultPath WRITE setDefaultPath)

    Q_PROPERTY(QString browseDialogTitle READ browseDialogTitle WRITE setBrowseDialogTitle)
    Q_PROPERTY(QString browseDialogDir READ browseDialogDir WRITE setBrowseDir)
    Q_PROPERTY(QString browseDialogFilter READ browseDialogFilter WRITE setBrowseFiler)

public:
    enum BrowserType { File, Folder };
    Q_ENUMS(BrowserType)

    explicit QBrowse(QWidget *parent = nullptr);
    explicit QBrowse(const QString &text = "", QWidget *parent = nullptr);
    ~QBrowse();

    QSize sizeHint() const override;

    BrowserType browserType() const;
    void setBrowserType(const BrowserType type);

    bool showDefaultButton() const;

    QString label() const;
    void setLabel(const QString& text);
    QString path() const;
    void setPath(const QString& path);
    QString placeholder() const;
    void setPlaceholder(const QString& text);
    QString buttonText() const;
    void setButtonText(const QString& text);
    QString defaultButtonText() const;
    void setDefaultButtonText(const QString& text);
    QString defaultPath() const;
    void setDefaultPath(const QString& path);

    QString browseDialogTitle() const;
    void setBrowseDialogTitle(const QString& title);
    QString browseDialogDir() const;
    void setBrowseDir(const QString& dir);
    QString browseDialogFilter() const;
    void setBrowseFiler(const QString& filters);

public Q_SLOT:
    void setShowDefaultButton(const bool show);

private:
    void setupUi();
    void setupConnections();

    void setDefaultButtonWidth();

private Q_SLOT:
    void openBrowseDialog();
    void setDefault();

private:
    QHBoxLayout* mLayout;

    QLabel* mLabel;
    QLineEdit* mLineEdit;
    QPushButton* mBrowseButton;
    QPushButton* mDefaultButton;
    QFontMetrics mDefaultButtonFont;

    BrowserType mBrowserType;
    bool mShowDefaultButton;
    QString mDefaultPath;

    QString mBrowseDialogTitle;
    QString mBrowseDialogDir;
    QString mBrowseDialogFilter;
};

