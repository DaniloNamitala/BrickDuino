#include "Spoiler.h"
#include <QPropertyAnimation>
#include <QStyleFactory>

Spoiler::Spoiler(const QString & title, QString color, QWidget *parent) : QWidget(parent) {
    this->title = title;
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

    mainLayout.setContentsMargins(0, 0, 0, 0);
    mainLayout.addWidget(&toggleButton);
    mainLayout.addWidget(&contentArea);
    setLayout(&mainLayout);

    QObject::connect(&toggleButton, &QToolButton::clicked, [this](const bool checked) {
        toggleButton.setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
        contentArea.setVisible(checked);
    });
}

QString Spoiler::getTitle() {
    return this->title;
}

void Spoiler::addWidget(QWidget* widget) {
    contentArea.layout()->addWidget(widget);
    contentArea.setFixedHeight(contentArea.layout()->sizeHint().height());
}