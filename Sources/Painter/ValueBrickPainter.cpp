#include "ValueBrickPainter.h"
#include "Util.h"

void ValueBrickPainter::paint(IPaintableBrick* brick, QPaintEvent* event) {
    QPainterPath path;
    QWidget* widget = brick->getWidget();
    QPainter painter(widget);

    QPen pen = brick->getContourPen();


    // Draw the shape of the brick
    path.moveTo(widget->height() / 2 , 0);
    path.arcTo(0, 0, widget->height(), widget->height(), 90, 180);
    path.lineTo(widget->width() - (widget->height() / 2), 0 + widget->height());
    path.arcTo(widget->width() - widget->height(), 0, widget->height(), widget->height(), 270, 180);
    path.lineTo((widget->height() / 2), 0);

    painter.setFont(Util::font());

    painter.setBrush(brick->getColor());
    painter.setPen(pen);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    int funcNameWidth = Util::textSize(brick->getName(), Util::font()).width();
    int x = MARGIN + funcNameWidth + MARGIN;
    
    QList<Parameter> params = brick->getParams();
    for (int i = 0; i < params.size(); i++) {
        params[i].paint(&painter, QPoint(x, VALUE_BRICK_MARGIN));
        x += params[i].size(Util::font()).width() + MARGIN;
    }

    painter.setPen(Util::textPen());
    painter.drawText(MARGIN, VALUE_BRICK_MARGIN + Util::textSize(brick->getName(), Util::font()).height(), brick->getName());

    painter.end();
}