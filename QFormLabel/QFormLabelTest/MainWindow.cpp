#include "MainWindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

#include "QFormLabel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(400, 400);
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout(this);
    centralWidget()->setLayout(layout);

    QLabel* title = new QLabel(tr("QFormLabel\nBy Lorenzo"), this);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    mFormLabel = new QFormLabel(this);
    mFormLabelUnlayered = new QFormLabel(this);

    QLineEdit *text = new QLineEdit(mFormLabel->text(), this);
    connect(text, &QLineEdit::textChanged, mFormLabel, &QFormLabel::setText);
    connect(text, &QLineEdit::textChanged, mFormLabelUnlayered, &QFormLabel::setText);

    QLineEdit *value = new QLineEdit(mFormLabel->value(), this);
    connect(value, &QLineEdit::textChanged, mFormLabel, QOverload<const QString&>::of(&QFormLabel::setValue));
    connect(value, &QLineEdit::textChanged, mFormLabelUnlayered, QOverload<const QString&>::of(&QFormLabel::setValue));

    QLineEdit *unit = new QLineEdit(mFormLabel->unit(), this);
    connect(unit, &QLineEdit::textChanged, mFormLabel, &QFormLabel::setUnit);
    connect(unit, &QLineEdit::textChanged, mFormLabelUnlayered, &QFormLabel::setUnit);

    QComboBox *alignment = new QComboBox(this);
    QStringList alignmentType = {"Left", "Center"};
    alignment->addItems(alignmentType);
    connect(alignment, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){ mFormLabel->setTextAlignment(static_cast<QFormLabel::TextAlignment>(index)); mFormLabelUnlayered->setTextAlignment(static_cast<QFormLabel::TextAlignment>(index)); });

    QLabel* unlayeredTitle = new QLabel(tr("Unlayered widget"), this);

    layout->addWidget(title);
    layout->addWidget(mFormLabel);
    layout->addWidget(text);
    layout->addWidget(value);
    layout->addWidget(unit);
    layout->addWidget(alignment);
    layout->addWidget(unlayeredTitle);
    layout->addStretch();

    int offset = 200;
    mFormLabelUnlayered->move(5, offset);
}

MainWindow::~MainWindow()
{
}

