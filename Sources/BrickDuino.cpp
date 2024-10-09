#include "BrickDuino.h"
#include "Board.h"
#include "ToolboxBrick.h"
#include "StatementBrick.h"
#include "Spoiler.h"

BrickDuino::BrickDuino(QWidget* parent) {
    crteateBlockBoard();
    crteateBlockToolbox();
}

void BrickDuino::crteateBlockBoard() {
    blockBoard = new Board(BOARD_BACKGROUND_COLOR);
    this->setCentralWidget(blockBoard);
}

void BrickDuino::crteateBlockToolbox() {
    blockToolbox = new QDockWidget(tr("Blocks"), this);
    blockToolbox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    blockToolbox->setMinimumWidth(200);
    blockToolbox->setAllowedAreas(Qt::LeftDockWidgetArea |
                                  Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, blockToolbox);

    QBoxLayout* layout = new QVBoxLayout();
    QScrollArea* scrollArea = new QScrollArea();
    QWidget* w = new QWidget();

    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    w->setLayout(layout);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: #1B1B1B; }");
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(w);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 0, 0);
    blockToolbox->setWidget(scrollArea); 
    
    StatementBrick* b1 = new StatementBrick(nullptr, "SE", QColor(0, 128, 0));
    b1->addParam(Parameter(ValueType::BOOL));

    StatementBrick* b2 = new StatementBrick(nullptr, "ENQUANTO", QColor(0, 128, 0));
    b2->addParam(Parameter(ValueType::BOOL));

    StatementBrick* b3 = new StatementBrick(nullptr, "SWITCH", QColor(0, 128, 0));
    b3->addParam(Parameter(ValueType::BOOL));

    Spoiler* spoiler = new Spoiler("Controle");
    spoiler->addWidget(b1);
    spoiler->addWidget(b2);
    spoiler->addWidget(b3);

    ToolboxBrick* B4 = new ToolboxBrick("ESCREVE", QColor(0, 128, 0));
    B4->addParam(Parameter(ValueType::BOOL));

    Spoiler* spoiler2 = new Spoiler("Saída");
    spoiler2->addWidget(B4);

    layout->addWidget(spoiler);
    layout->addWidget(spoiler2);


}

BrickDuino::~BrickDuino() {}