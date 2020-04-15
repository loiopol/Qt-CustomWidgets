#include "MainWindow.h"

#include <QLayout>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout(this);
    centralWidget()->setLayout(layout);

    QLabel* title = new QLabel("QSwitch\nBy Lorenzo", this);
    title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QSwitchKnob* switchKnob = new QSwitchKnob(this);
    QSwitchKnob* unlayerSwitchKnob = new QSwitchKnob(this);

    QSwitchSlider* switchSlider = new QSwitchSlider(this);
    QSwitchSlider* unlayeredSwitchSlider = new QSwitchSlider(this);

    switchObject = new QSwitchIndicator(false, true, this);
    unlayeredSwitchObject = new QSwitchIndicator(true, false, this);
    unlayeredSwitchObjectOff = new QSwitchIndicator(true, false, this);
    unlayeredSwitchObjectOff->setEnabled(false);

    mSwitch = new QSwitch(this);
    mSwitchNoLabels = new QSwitch(true, false, true, this);
    mUnlayerSwitch = new QSwitch(true, true, true, this);
    mUnlayerSwitchNoLabels = new QSwitch(true, false, false, this);

    QSpinBox* barMinLength = new QSpinBox(this);
    barMinLength->setValue(switchObject->maximumBarWidth());
    barMinLength->setMaximum(200);
    connect(barMinLength, QOverload<int>::of(&QSpinBox::valueChanged), mSwitch, &QSwitch::setMaximumBarWidth);
    connect(barMinLength, QOverload<int>::of(&QSpinBox::valueChanged), mSwitchNoLabels, &QSwitch::setMaximumBarWidth);
    connect(barMinLength, QOverload<int>::of(&QSpinBox::valueChanged), mUnlayerSwitch, &QSwitch::setMaximumBarWidth);
    connect(barMinLength, QOverload<int>::of(&QSpinBox::valueChanged), mUnlayerSwitchNoLabels, &QSwitch::setMaximumBarWidth);
    connect(barMinLength, QOverload<int>::of(&QSpinBox::valueChanged), switchObject, &QSwitchIndicator::setMaximumBarWidth);

    QCheckBox *showLabel = new QCheckBox("Labels Visible", this);
    showLabel->setChecked(mSwitch->labelsVisible());
    connect(showLabel, &QCheckBox::stateChanged, mSwitch, &QSwitch::setLabelsVisible);
    connect(showLabel, &QCheckBox::stateChanged, mUnlayerSwitch, &QSwitch::setLabelsVisible);

    QCheckBox* barWidth = new QCheckBox("Bar = Knob", this);
    barWidth->setChecked(mSwitch->fullSize());
    connect(barWidth, &QCheckBox::stateChanged, mSwitch, &QSwitch::setFullSize);
    connect(barWidth, &QCheckBox::stateChanged, mUnlayerSwitch, &QSwitch::setFullSize);
    connect(barWidth, &QCheckBox::stateChanged, unlayeredSwitchObjectOff, &QSwitchIndicator::setFullSize);

    QLineEdit *offText = new QLineEdit(this);
    offText->setText(mSwitch->offText());
    connect(offText, &QLineEdit::textChanged, mSwitch, &QSwitch::setOffText);
    connect(offText, &QLineEdit::textChanged, mUnlayerSwitch, &QSwitch::setOffText);

    QLineEdit *onText = new QLineEdit(this);
    onText->setText(mSwitch->onText());
    connect(onText, &QLineEdit::textChanged, mSwitch, &QSwitch::setOnText);
    connect(onText, &QLineEdit::textChanged, mUnlayerSwitch, &QSwitch::setOnText);

    QPushButton* choseColor = new QPushButton("Chose Color", this);
    connect(choseColor, &QPushButton::clicked, this, &MainWindow::setNewKnobColor);

    QCheckBox* activateSwitch = new QCheckBox("Set Active", this);
    activateSwitch->setChecked(mSwitch->isActive());
    connect(activateSwitch, &QCheckBox::stateChanged, mSwitch, &QSwitch::setActive);
    connect(activateSwitch, &QCheckBox::stateChanged, mSwitchNoLabels, &QSwitch::setActive);
    connect(activateSwitch, &QCheckBox::stateChanged, mUnlayerSwitch, &QSwitch::setActive);
    connect(activateSwitch, &QCheckBox::stateChanged, mUnlayerSwitchNoLabels, &QSwitch::setActive);
    connect(activateSwitch, &QCheckBox::stateChanged, switchObject, &QSwitchIndicator::setActive);
    connect(activateSwitch, &QCheckBox::stateChanged, unlayeredSwitchObject, &QSwitchIndicator::setActive);
    connect(activateSwitch, &QCheckBox::stateChanged, unlayeredSwitchObjectOff, &QSwitchIndicator::setActive);

    QLabel* switchState = new QLabel(this);
    switchState->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    switchState->setText(tr("State: %1").arg(mSwitch->isActive() ? "Enabled" : "Disabled"));
    connect(mSwitch, &QSwitch::triggered, [this, switchState](const bool isActive){ switchState->setText(tr("State: %1").arg(isActive ? "Enabled" : "Disabled")); });

    int offset = 400;
    unlayerSwitchKnob->move(0, offset);
    unlayeredSwitchSlider->move(0, offset + 30);
    unlayeredSwitchObject->move(0, offset + 60);
    unlayeredSwitchObjectOff->move(0, offset + 90);

    mUnlayerSwitch->move(0, offset + 120);
    mUnlayerSwitchNoLabels->move(0, offset + 150);

    layout->addWidget(title);
    layout->addWidget(switchKnob);
    layout->addWidget(switchSlider);
    layout->addWidget(switchObject);
    layout->addWidget(mSwitch);
    layout->addWidget(mSwitchNoLabels);
    layout->addWidget(barMinLength);
    layout->addWidget(showLabel);
    layout->addWidget(barWidth);
    layout->addWidget(offText);
    layout->addWidget(onText);
    layout->addWidget(choseColor);
    layout->addWidget(activateSwitch);
    layout->addWidget(switchState);
    QLabel *secondTitle = new QLabel("Unlayered widgets", this);
    secondTitle->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    layout->addWidget(secondTitle);
    layout->addStretch();
}


MainWindow::~MainWindow()
{
}

void MainWindow::setNewKnobColor()
{
    QColor newColor = QColorDialog::getColor(switchObject->onColor(), this, "Chose Color");
    if(!newColor.isValid())
        return;

    mSwitch->setOnColor(newColor);
    mSwitchNoLabels->setOnColor(newColor);
    mUnlayerSwitch->setOnColor(newColor);
    switchObject->setOnColor(newColor);
    unlayeredSwitchObject->setOnColor(newColor);
    unlayeredSwitchObjectOff->setOnColor(newColor);
    mUnlayerSwitchNoLabels->setOnColor(newColor);
}

