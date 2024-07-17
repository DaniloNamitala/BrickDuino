#include "Board.h"
#include "FunctionBrick.h"
#include "StatementBrick.h"
#include "Parameter.h"

Board::Board(QColor bgColor) {
    background = bgColor;
    setMouseTracking(true);

    Brick* b = new StatementBrick("Repita", QColor(255, 0, 0));
    b->addParam(Parameter("de", "", ParamType::INT));
    b->addParam(Parameter("ate", "", ParamType::INT));

    Brick* b1 = new FunctionBrick("Escreva no Serial", QColor(0, 128, 0));
    b1->addParam(Parameter("", "", ParamType::STRING));
    ((StatementBrick*)b)->addBrick(b1);

    b1 = new FunctionBrick("AnalogWrite", QColor(0, 128, 0));
    b1->addParam(Parameter("Porta:", "", ParamType::STRING));
    b1->addParam(Parameter("Valor:", "", ParamType::STRING));
    ((StatementBrick*)b)->addBrick(b1);

    b1 = new FunctionBrick("AnalogRead", QColor(0, 128, 0));
    b1->addParam(Parameter("Porta:", "", ParamType::STRING));
    ((StatementBrick*)b)->addBrick(b1);
    
    bricks.append(new StatementBrick("Loop", QColor(150, 75, 0)));
    ((StatementBrick*)bricks[0])->addBrick(b);
    ((StatementBrick*)bricks[0])->addBrick(new FunctionBrick("Funcao", QColor(0, 0, 128)));
    
}

void Board::paintEvent(QPaintEvent *event)
{   
    painter.begin(this);
    painter.fillRect(event->rect(), background);
    int top = 10;
    for(int i = 0; i < bricks.size(); i++) {
        bricks[i]->paint(&painter, QPoint(10, top));
        top += bricks[i]->height();
    }
    painter.end();
}

void Board::mouseMoveEvent(QMouseEvent *event) { 
    
}