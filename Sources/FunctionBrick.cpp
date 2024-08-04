#include "FunctionBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"

FunctionBrick::FunctionBrick(QWidget* parent, const char* name, QColor color) : Brick(parent, name, color) { 

}

void FunctionBrick::paintEvent(QPaintEvent* event) {
    QPainterPath path;
    QPainter painter(this);

    // Draw the pin
    path.moveTo(2 * EDGE_RADIUS, PIN_H);
    path.arcTo(2 * EDGE_RADIUS, 0, 2 * PIN_H, 2 * PIN_H, 180, -180);

    // Draw the right corners
    path.lineTo(width() - 2 * EDGE_RADIUS, PIN_H);
    path.arcTo(width() - 2 * EDGE_RADIUS, PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    path.lineTo(width(), height() - 2 * EDGE_RADIUS);
    path.arcTo(width() - 2 * EDGE_RADIUS, height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);

    // Draw the socket
    path.lineTo(2 * EDGE_RADIUS + (PIN_H + contourPen.width()) * 2, height());
    path.arcTo(2 * EDGE_RADIUS - contourPen.width(), height() - (PIN_H + contourPen.width()), 2 * (PIN_H + contourPen.width()), 2 * (PIN_H + contourPen.width()), 0, 180);

    // Draw the left corners
    path.lineTo(2 * EDGE_RADIUS - contourPen.width(), height());
    path.arcTo(0, height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 270, -90);
    path.lineTo(0, 2 * EDGE_RADIUS + PIN_H);
    path.arcTo(0, PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 180, -90);
    path.lineTo(2 * EDGE_RADIUS, PIN_H);

    painter.setFont(Util::font());

    painter.setBrush(getColor());
    painter.setPen(contourPen);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    int funcNameWidth = Util::textSize(functionName, Util::font()).width();
    int x = MARGIN + funcNameWidth + MARGIN;
    
    for (int i = 0; i < params.size(); i++) {
        params[i].paint(&painter, QPoint(x, MARGIN + PIN_H));
        x += params[i].size(Util::font()).width() + MARGIN;
    }

    painter.setPen(Util::textPen());
    painter.drawText(MARGIN, MARGIN + Util::textSize(functionName, Util::font()).height()+ PIN_H, functionName);

    painter.end();
}