#include "StatementBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"

StatementBrick::StatementBrick(const char* name, QColor color) : Brick(name, color) { }

void StatementBrick::paint(QPainter *painter, QPoint origin) {
    QPainterPath path;
    this->origin = origin;

    // Draw the pin
    path.moveTo(2 * EDGE_RADIUS, 0);
    path.arcTo(2 * EDGE_RADIUS, -PIN_H, 2 * PIN_H, 2 * PIN_H, 180, -180);

    // Draw the right corners
    path.lineTo(width() - 2 * EDGE_RADIUS, 0);
    path.arcTo(width() - 2 * EDGE_RADIUS, 0, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    path.lineTo(width(), headerHeight() - 2 * EDGE_RADIUS);
    path.arcTo(width() - 2 * EDGE_RADIUS, headerHeight() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);

    // Draw the socket
    path.lineTo(BRACKET_WIDTH + 2 * EDGE_RADIUS + (PIN_H + getPen().width()) * 2, headerHeight());
    path.arcTo(BRACKET_WIDTH + 2 * EDGE_RADIUS - getPen().width(), headerHeight() - (PIN_H + getPen().width()), 2 * (PIN_H + getPen().width()), 2 * (PIN_H + getPen().width()), 0, 180);

    path.lineTo(BRACKET_WIDTH + EDGE_RADIUS, headerHeight());
    path.arcTo(BRACKET_WIDTH, headerHeight(), 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, 90);

    path.lineTo(BRACKET_WIDTH, height() - BRACKET_WIDTH - EDGE_RADIUS);
    path.arcTo(BRACKET_WIDTH, height() - BRACKET_WIDTH - 2*EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 180, 90);

    
    path.lineTo(width() - 2 * EDGE_RADIUS, height() - BRACKET_WIDTH);
    path.arcTo(width() - 2 * EDGE_RADIUS, height() - BRACKET_WIDTH, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    path.lineTo(width(), height() - 2 * EDGE_RADIUS);
    path.arcTo(width() - 2 * EDGE_RADIUS, height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);

    // Draw the socket
    path.lineTo(2 * EDGE_RADIUS + (PIN_H + getPen().width()) * 2, height());
    path.arcTo(2 * EDGE_RADIUS - getPen().width(), height() - (PIN_H + getPen().width()), 2 * (PIN_H + getPen().width()), 2 * (PIN_H + getPen().width()), 0, 180);

    // Draw the bottom left corner
    path.lineTo(2 * EDGE_RADIUS - getPen().width(), height());
    path.arcTo(0, height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 270, -90);
    path.lineTo(0, 2 * EDGE_RADIUS);
    path.arcTo(0, 0, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 180, -90);
    path.lineTo(2 * EDGE_RADIUS, 0);

    painter->setFont(getFont());

    painter->setBrush(getColor());
    painter->setPen(getPen());

    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(origin);
    painter->drawPath(path);

    int funcNameWidth = Util::textSize(functionName, getFont()).width();
    int x = MARGIN + funcNameWidth + MARGIN;
    
    for (int i = 0; i < params.size(); i++) {
        params[i].paint(painter, QPoint(x, MARGIN));
        x += params[i].size(getFont()).width() + MARGIN;
    }

    QPoint point = getStatementOrigin();
    for (int i = 0; i < bricks.size(); i++) {
        bricks[i]->paint(painter, point);
        point.setY(point.y() + bricks[i]->height());
    }

    painter->setPen(getTextPen());
    painter->drawText(MARGIN, MARGIN + Util::textSize(functionName, getFont()).height(), functionName);

    painter->translate(-origin);
    
}

int StatementBrick::headerHeight() {
    return Brick::height();
}

int StatementBrick::height() {
    int instructionsHeight = 0;
    for (int i = 0; i < bricks.size(); i++) {
        instructionsHeight += bricks[i]->height();
    }

    if (instructionsHeight == 0) instructionsHeight = EMPTY_STATEMENT_GAP;
    return instructionsHeight + headerHeight() + BRACKET_WIDTH;
}

QPoint StatementBrick::getStatementOrigin() {
    return QPoint(BRACKET_WIDTH, headerHeight());
}

void StatementBrick::addBrick(Brick* brick) {
    bricks.append(brick);
}