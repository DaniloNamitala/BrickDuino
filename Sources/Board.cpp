#include "Board.h"
#include "FunctionBrick.h"
#include "StatementBrick.h"
#include "Parameter.h"
#include "Shadow.h"	

Board::Board(QColor bgColor) {
    background = bgColor;
    setMouseTracking(true);

    Brick* b1 = new FunctionBrick(this, "Analog Write", QColor(0, 128, 0));
    b1->addParam(Parameter(ValueType::STRING));
    b1->move(QPoint(10, 10));
    bricks.append(b1);

    Brick* b2 = new FunctionBrick(this, "Analog Read", QColor(0, 128, 0));
    b2->addParam(Parameter(ValueType::STRING));
    bricks.append(b2);
    b1->attach(b2);

    Brick* b3 = new FunctionBrick(this, "Escreva no Serial", QColor(0, 128, 0));
    b3->addParam(Parameter(ValueType::STRING));
    bricks.append(b3);
    b2->attach(b3);

    StatementBrick* b4 = new StatementBrick(this, "Escreva no Serial", QColor(0, 128, 0));
    b4->addParam(Parameter(ValueType::STRING));
    b4->move(QPoint(10, 10));
    bricks.append(b4);
    b4->insertBrick(b1);

    Brick* b5 = new FunctionBrick(this, "Escreva no Serial", QColor(0, 128, 0));
    b5->addParam(Parameter(ValueType::STRING));
    bricks.append(b5);
    b4->attach(b5);

}

void Board::paintEvent(QPaintEvent *event)
{   
    painter.begin(this);
    painter.fillRect(event->rect(), background);
    painter.end();
}

void Board::mouseMoveEvent(QMouseEvent *event) { 
    
}