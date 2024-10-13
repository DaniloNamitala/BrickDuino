#include "BinaryOperatorPainter.h"
#include "Util.h"

void BinaryOperatorPainter::paint(IPaintableBrick* brick, QPaintEvent* event) {
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

    int x = MARGIN;
    QList<Parameter> params = brick->getParams();
    if (params.size() > 0) {
        params[0].paint(&painter, QPoint(x, VALUE_BRICK_MARGIN));
        x += params[0].size(Util::font()).width() + MARGIN;
    }

    int funcNameWidth = Util::textSize(brick->getName(), Util::font()).width();
    painter.setPen(Util::textPen());
    painter.drawText(x, VALUE_BRICK_MARGIN + Util::textSize(brick->getName(), Util::font()).height(), brick->getName());

    painter.setPen(pen);
    x += funcNameWidth + MARGIN;
    if (params.size() > 1) {
        params[1].paint(&painter, QPoint(x, VALUE_BRICK_MARGIN));
        x += params[1].size(Util::font()).width() + MARGIN;
    }

    painter.end();
}