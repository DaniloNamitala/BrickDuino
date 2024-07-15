#include "BrickDuino.h"
#include "Board.h"

BrickDuino::BrickDuino(QWidget* parent) {
    Board* b = new Board(QColor(0x1B1B1B));
    QLayout* layout = new QHBoxLayout();
    QWidget* central = new QWidget(this);

    central->setLayout(layout);  
    b->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    layout->addWidget(b);
    this->setCentralWidget(central);
}

BrickDuino::~BrickDuino()  {

}