#include "QBrowse.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

#include <QSize>

QBrowse::QBrowse(QWidget *parent) :
    QWidget(parent),
    mLayout(new QHBoxLayout(this)),
    mLabel(new QLabel("Label", this)),
    mLineEdit(new QLineEdit(this)),
    mBrowseButton(new QPushButton(tr("Browse.."), this)),
    mDefaultButton(new QPushButton(tr("D"), this)),
    mDefaultButtonFont(mDefaultButton->font()),
    mBrowserType(File),
    mShowDefaultButton(true),
    mDefaultPath(),
    mBrowseDialogTitle(QString("Chose a " + QString(mBrowserType == File ? "file" : "folder"))),
    mBrowseDialogDir("/home"),
    mBrowseDialogFilter()
{
    setupUi();
    setupConnections();
}

QBrowse::QBrowse(const QString& text, QWidget *parent) :
    QWidget(parent),
    mLayout(new QHBoxLayout(this)),
    mLabel(new QLabel(text, this)),
    mLineEdit(new QLineEdit(this)),
    mBrowseButton(new QPushButton(tr("Browse.."), this)),
    mDefaultButton(new QPushButton(tr("D"), this)),
    mDefaultButtonFont(mDefaultButton->font()),
    mBrowserType(File),
    mShowDefaultButton(true),
    mDefaultPath(),
    mBrowseDialogTitle(QString("Chose a " + QString(mBrowserType == File ? "file" : "folder"))),
    mBrowseDialogDir("/home"),
    mBrowseDialogFilter()
{
    setupUi();
    setupConnections();
}

QBrowse::~QBrowse()
{
    delete mLabel;
    delete mLineEdit;
    delete mBrowseButton;
    delete mDefaultButton;

    delete mLayout;
}

QSize QBrowse::sizeHint() const
{
    int width = 0;
    QFontMetrics fm(mLabel->font());
    QSize sz = fm.size(Qt::TextShowMnemonic, mLabel->text());
    width += sz.width();

    width += 100;
    width += mBrowseButton->sizeHint().width();
    width += mDefaultButton->sizeHint().width();

    QMargins margins = contentsMargins();
    return QSize(width, mLabel->height() + 18);
}

QBrowse::BrowserType QBrowse::browserType() const
{
    return mBrowserType;
}

void QBrowse::setBrowserType(const QBrowse::BrowserType type)
{
    if(mBrowserType == type)
        return;
    mBrowserType = type;
}

bool QBrowse::showDefaultButton() const
{
    return mShowDefaultButton;
}

QString QBrowse::label() const
{
    return mLabel->text();
}

void QBrowse::setLabel(const QString &text)
{
    mLabel->setText(text);
}

QString QBrowse::path() const
{
    return mLineEdit->text();
}

void QBrowse::setPath(const QString &path)
{
    mLineEdit->setText(path);
}

QString QBrowse::placeholder() const
{
    return mLineEdit->placeholderText();
}

void QBrowse::setPlaceholder(const QString &text)
{
    mLineEdit->setPlaceholderText(text);
}

QString QBrowse::buttonText() const
{
    return mBrowseButton->text();
}

void QBrowse::setButtonText(const QString &text)
{
    mBrowseButton->setText(text);
}

QString QBrowse::defaultButtonText() const
{
    return mDefaultButton->text();
}

void QBrowse::setDefaultButtonText(const QString &text)
{
    mDefaultButton->setText(text);
    setDefaultButtonWidth();
}

QString QBrowse::defaultPath() const
{
    return mDefaultPath;
}

void QBrowse::setDefaultPath(const QString &path)
{
    if(mDefaultPath == path)
        return;
    mDefaultPath = path;
}

QString QBrowse::browseDialogTitle() const
{
    return mBrowseDialogTitle;
}

void QBrowse::setBrowseDialogTitle(const QString &title)
{
    if(mBrowseDialogTitle == title)
        return;
    mBrowseDialogTitle = title;
}

QString QBrowse::browseDialogDir() const
{
    return mBrowseDialogDir;
}

void QBrowse::setBrowseDir(const QString &dir)
{
    if(mBrowseDialogDir == dir)
        return;
    mBrowseDialogDir = dir;
}

QString QBrowse::browseDialogFilter() const
{
    return mBrowseDialogFilter;
}

void QBrowse::setBrowseFiler(const QString &filters)
{
    if(mBrowseDialogFilter == filters)
        return;
    mBrowseDialogFilter = filters;
}

void QBrowse::setShowDefaultButton(const bool show)
{
    if(mShowDefaultButton == show)
        return;
    mShowDefaultButton = show;
    mDefaultButton->setVisible(mShowDefaultButton);
}

void QBrowse::setupUi()
{
    mLayout->setMargin(3);

    mLayout->addWidget(mLabel);
    mLayout->addWidget(mLineEdit);
    mLayout->addWidget(mBrowseButton);
    mLayout->addWidget(mDefaultButton);

    setDefaultButtonWidth();
    setShowDefaultButton(false);

    setLayout(mLayout);

    adjustSize();
}

void QBrowse::setupConnections()
{
    connect(mBrowseButton, &QPushButton::clicked, this, &QBrowse::openBrowseDialog);
    connect(mDefaultButton, &QPushButton::clicked, this, &QBrowse::setDefault);
}

void QBrowse::setDefaultButtonWidth()
{
    int width = mDefaultButtonFont.horizontalAdvance(mDefaultButton->text()) + 10;
    mDefaultButton->setMaximumWidth(width < 25 ? 25 : width);
}

void QBrowse::openBrowseDialog()
{
    QString path;
    switch (mBrowserType) {
    case File:
        path = QFileDialog::getOpenFileName(this, mBrowseDialogTitle, mBrowseDialogDir, mBrowseDialogFilter);
        break;
    case Folder:
        path = QFileDialog::getExistingDirectory(this, mBrowseDialogTitle, mBrowseDialogDir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        break;
    }

    if(path == "")
        return;
    setPath(path);
}

void QBrowse::setDefault()
{
    if(mDefaultPath == "")
        return;
    mLineEdit->setText(mDefaultPath);
}
