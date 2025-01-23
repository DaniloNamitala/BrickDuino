#include "Spoiler.h"
#include <QPropertyAnimation>
#include <QStyleFactory>

Spoiler::Spoiler(const QString & title, QString color, QWidget *parent) : QWidget(parent) {
    this->title = title;
    this->color = QColor(color);
    toggleButton.setStyleSheet("QToolButton { border: none; background-color:"+ color +"; color: white; font-size: 15px }");
    toggleButton.setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toggleButton.setArrowType(Qt::ArrowType::RightArrow);
    toggleButton.setText(title);
    toggleButton.setCheckable(true);
    toggleButton.setChecked(false);
    toggleButton.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QVBoxLayout* contentLayout = new QVBoxLayout();
    contentLayout->setAlignment(Qt::AlignTop);
    contentArea.setLayout(contentLayout);
    contentArea.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    contentArea.setVisible(false);

    buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignTop);
    contentLayout->addLayout(buttonLayout);

    mainLayout.setContentsMargins(0, 0, 0, 0);
    mainLayout.addWidget(&toggleButton);
    mainLayout.addWidget(&contentArea);
    setLayout(&mainLayout);

    QObject::connect(&toggleButton, &QToolButton::clicked, [this](const bool checked) {
        toggleButton.setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
        contentArea.setVisible(checked);
    });
}

QColor Spoiler::getColor() {
    return color;
}

QString Spoiler::getTitle() {
    return this->title;
}

void Spoiler::addActionButton(QWidget* widget) {
    buttonLayout->addWidget(widget);
    contentArea.setFixedHeight(contentArea.layout()->sizeHint().height());
}

void Spoiler::addWidget(QWidget* widget) {
    contentArea.layout()->addWidget(widget);
    contentArea.setFixedHeight(contentArea.layout()->sizeHint().height() + buttonLayout->sizeHint().height());
}