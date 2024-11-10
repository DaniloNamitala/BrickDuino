#include "ConfigBrickIf.h"
using namespace Workspace;

#include "ToolboxStatementBrick.h"

ConfigBrickIf::ConfigBrickIf(StatementBrick* brick, QString name) : QDialog(brick->getWidget()) {
    this->_brick = brick;
    setModal(true);

    QGridLayout* layout = new QGridLayout();

    QPushButton* btnAddIf = new QPushButton("+");
    QPushButton* btnRemoveIf = new QPushButton("-");
    QPushButton* btnAddElse = new QPushButton("+");
    QPushButton* btnRemoveElse = new QPushButton("-");

    connect(btnAddIf, &QPushButton::clicked, [=]() {
        if (name == "case_statement")
            brick->addCase();
        else
            brick->addCondition();
    });

    connect(btnRemoveIf, &QPushButton::clicked, [=]() {
        if (name == "case_statement")
            brick->removeCase();
        else
            brick->removeCondition();
    });

    connect(btnAddElse, &QPushButton::clicked, [=]() {
        brick->addElse();
    });

    connect(btnRemoveElse, &QPushButton::clicked, [=]() {
        brick->removeElse();
    });

    QLabel* lblCondition = new QLabel("ELSE IF");
    if (name == "case_statement")
        lblCondition->setText("CASO");
    QLabel* lblElse = new QLabel("ELSE");

    layout->addWidget(lblCondition, 0, 0, 1, 2, Qt::AlignHCenter);
    layout->addWidget(btnAddIf, 1, 0);
    layout->addWidget(btnRemoveIf, 1, 1);
    if (name == "if_statement") {
        layout->addWidget(lblElse, 2, 0, 1, 2, Qt::AlignHCenter);
        layout->addWidget(btnAddElse, 3, 0);
        layout->addWidget(btnRemoveElse, 3, 1);
    }

    layout->setContentsMargins(10, 10, 10, 10);
    setLayout(layout);
}