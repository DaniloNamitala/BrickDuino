#include "Board.h"
#include "Brick.h"
#include "Parameter.h"

Board::Board(QColor bgColor) {
    background = bgColor;
    setMouseTracking(true);

    bricks.append(new Brick("Repita", QColor(255, 0, 0)));
    bricks[0]->addParam(Parameter("de", "", ParamType::INT));
    bricks[0]->addParam(Parameter("ate", "", ParamType::INT));

    bricks.append(new Brick("Escreva", QColor(0, 128, 0)));
    bricks[1]->addParam(Parameter("", "", ParamType::STRING));
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
    // this->setCursor(Qt::ArrowCursor);
    // for(int i = 0; i < bricks.size(); i++) {
    //     if(bricks[i]->isOver(event->pos())) {
    //         bricks[i]->mouseMove(event);
    //         this->setCursor(Qt::PointingHandCursor);
    //     }
    // }
    // update();
}