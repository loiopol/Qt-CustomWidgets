#include "MainWindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

#include "QLedIndicator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(400, 400);
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout(this);
    centralWidget()->setLayout(layout);

    QLabel* title = new QLabel(tr("QFormLabel\nBy Lorenzo"), this);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    mLed = new QLedIndicator("Test di prova", QLedIndicator::Bottom, this);
    mLedUnlayered = new QLedIndicator("Test di prova", QLedIndicator::Bottom, this);

    QComboBox *state = new QComboBox(this);
    QStringList stateName = {"Red", "Disabled", "Green", "Yellow"};
    state->addItems(stateName);
    state->setCurrentIndex(1);
    connect(state, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){ mLed->setLedState(index-1); mLedUnlayered->setLedState(index-1); });

    QLineEdit *text = new QLineEdit(mLed->text(), this);
    connect(text, &QLineEdit::textChanged, mLed, &QLedIndicator::setText);
    connect(text, &QLineEdit::textChanged, mLedUnlayered, &QLedIndicator::setText);

    QComboBox *alignment = new QComboBox(this);
    QStringList alignmentType = {"Hide", "Left", "Top", "Right", "Bottom" };
    alignment->addItems(alignmentType);
    alignment->setCurrentIndex(4);
    connect(alignment, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index){ mLed->setLabelPosition(static_cast<QLedIndicator::LabelPosition>(index)); mLedUnlayered->setLabelPosition(static_cast<QLedIndicator::LabelPosition>(index)); });

    QLabel* unlayeredTitle = new QLabel(tr("Unlayered widget"), this);

    layout->addWidget(title);
    layout->addWidget(mLed);
    layout->addWidget(state);
    layout->addWidget(text);
    layout->addWidget(alignment);
    layout->addWidget(unlayeredTitle);
    layout->addStretch();

    int offset = 200;
    mLedUnlayered->move(5, offset);
}

MainWindow::~MainWindow()
{
}

