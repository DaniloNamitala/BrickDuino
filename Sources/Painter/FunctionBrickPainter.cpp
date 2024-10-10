#include "FunctionBrickPainter.h"
#include "Util.h"
#include "Parameter.h"

void FunctionBrickPainter::paint(IPaintableBrick* brick, QPaintEvent* event) {
    QPainterPath path;
    QWidget* widget = brick->getWidget();
    QPainter painter(widget);

    QPen pen = brick->getContourPen();

    // Draw the pin
    path.moveTo(2 * EDGE_RADIUS, PIN_H);
    path.arcTo(2 * EDGE_RADIUS, 0, 2 * PIN_H, 2 * PIN_H, 180, -180);

    // Draw the right corners
    path.lineTo(widget->width() - 2 * EDGE_RADIUS, PIN_H);
    path.arcTo(widget->width() - 2 * EDGE_RADIUS, PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    path.lineTo(widget->width(), widget->height() - 2 * EDGE_RADIUS);
    path.arcTo(widget->width() - 2 * EDGE_RADIUS, widget->height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);

    // Draw the socket
    path.lineTo(2 * EDGE_RADIUS + (PIN_H + pen.width()) * 2, widget->height());
    path.arcTo(2 * EDGE_RADIUS - pen.width(), widget->height() - (PIN_H + pen.width()), 2 * (PIN_H + pen.width()), 2 * (PIN_H + pen.width()), 0, 180);

    // Draw the left corners
    path.lineTo(2 * EDGE_RADIUS - pen.width(), widget->height());
    path.arcTo(0, widget->height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 270, -90);
    path.lineTo(0, 2 * EDGE_RADIUS + PIN_H);
    path.arcTo(0, PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 180, -90);
    path.lineTo(2 * EDGE_RADIUS, PIN_H);

    painter.setFont(Util::font());

    painter.setBrush(brick->getColor());
    painter.setPen(pen);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    int funcNameWidth = Util::textSize(brick->getName(), Util::font()).width();
    int x = MARGIN + funcNameWidth + MARGIN;
    
    QList<Parameter> params = brick->getParams();
    for (int i = 0; i < params.size(); i++) {
        params[i].paint(&painter, QPoint(x, MARGIN + PIN_H));
        x += params[i].size(Util::font()).width() + MARGIN;
    }

    painter.setPen(Util::textPen());
    painter.drawText(MARGIN, MARGIN + Util::textSize(brick->getName(), Util::font()).height()+ PIN_H, brick->getName());

    painter.end();
}