#include "Brick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"

Brick::Brick(const char* name, QColor color) {
    this->color = color;
    hovered = false;

    functionName = QString(name);
}

void Brick::addParam(Parameter param) {
    params.append(param);
}

void Brick::paint(QPainter *painter, QPoint origin) {
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
    painter->drawText(MARGIN, height()/2+3, functionName);

    painter->translate(-origin);
    
}

QColor Brick::getColor() {
    return hovered ? color.darker(150) : color;
}

bool Brick::isOver(QPoint point) { 
    QRect rect(origin, QSize(width(), height()));
    hovered = rect.contains(point);
    return hovered;
}

bool Brick::mouseMove(QMouseEvent *event) { 
    return false;
}

QPen Brick::getPen() {
    QPen pen(color.darker(300));
    pen.setWidth(2);
    return pen;
}

QPen Brick::getTextPen() {
    QPen textPen(QColor(255, 255, 255));
    textPen.setWidth(3);
    return textPen;
}

int Brick::width() { 
    QFontMetrics fm(getFont());
    int funcNameWidth = fm.horizontalAdvance(functionName);
    int paramsWidth = 0;
    for (int i = 0; i < params.size(); i++) {
        paramsWidth += params[i].size(getFont()).width();
    }
    int width = funcNameWidth + paramsWidth;

    // margins between function name, parameters and the edges
    width += params.size() * MARGIN + 2*MARGIN; 
    return width;
}

int Brick::height() { 
    int height = 0;
    QFontMetrics fm(getFont());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size(getFont()).height());
    }
    height = qMax(height, fm.height());
    return height + 2*MARGIN;
}

QFont Brick::getFont() {
    return QFont("Arial", 10, QFont::Bold, false);
}

