#include "FunctionBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"

FunctionBrick::FunctionBrick(const char* name, QColor color) : Brick(name, color) { }

void FunctionBrick::paint(QPainter *painter, QPoint origin) {
    QPainterPath path;
    this->origin = origin;

    // Draw the pin
    path.moveTo(2 * EDGE_RADIUS, 0);
    path.arcTo(2 * EDGE_RADIUS, -PIN_H, 2 * PIN_H, 2 * PIN_H, 180, -180);

    // Draw the right corners
    path.lineTo(width() - 2 * EDGE_RADIUS, 0);
    path.arcTo(width() - 2 * EDGE_RADIUS, 0, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    path.lineTo(width(), height() - 2 * EDGE_RADIUS);
    path.arcTo(width() - 2 * EDGE_RADIUS, height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);

    // Draw the socket
    path.lineTo(2 * EDGE_RADIUS + (PIN_H + getPen().width()) * 2, height());
    path.arcTo(2 * EDGE_RADIUS - getPen().width(), height() - (PIN_H + getPen().width()), 2 * (PIN_H + getPen().width()), 2 * (PIN_H + getPen().width()), 0, 180);

    // Draw the left corners
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
    painter->setPen(getTextPen());
    painter->drawText(MARGIN, MARGIN + Util::textSize(functionName, getFont()).height(), functionName);
    painter->translate(-origin);
}