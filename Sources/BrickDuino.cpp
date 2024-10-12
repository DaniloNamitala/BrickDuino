#include "BrickDuino.h"
#include "Board.h"
#include "ToolboxFunctionBrick.h"
#include "ToolboxStatementBrick.h"
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
    
    Toolbox::StatementBrick* b = new Toolbox::StatementBrick("ENQUANTO", QColor(128, 128, 0));
    b->addParam(Parameter(ValueType::INT));

    Spoiler* spoiler = new Spoiler("Controle");
    spoiler->addWidget(b);

    Spoiler* spoiler2 = new Spoiler("Saída");
     
    Toolbox::Brick* b1 = new Toolbox::FunctionBrick("ESCREVE", QColor(0, 128, 0));
    b1->addParam(Parameter(ValueType::BOOL));
    b1->addParam(Parameter(ValueType::BOOL));
    spoiler2->addWidget(b1);

    b1 = new Toolbox::FunctionBrick("FUNCAO 1", QColor(0, 128, 0));
    b1->addParam(Parameter(ValueType::BOOL));
    spoiler2->addWidget(b1);

    b1 = new Toolbox::FunctionBrick("FUNCAO 2 TESTE COM NOME GRANDE", QColor(0, 128, 0));
    b1->addParam(Parameter(ValueType::BOOL));
    b1->addParam(Parameter(ValueType::BOOL));
    b1->addParam(Parameter(ValueType::BOOL));
    spoiler2->addWidget(b1);

    layout->addWidget(spoiler);
    layout->addWidget(spoiler2);
}

BrickDuino::~BrickDuino() {}