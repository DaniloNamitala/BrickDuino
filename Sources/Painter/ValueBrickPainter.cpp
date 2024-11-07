#include "ValueBrickPainter.h"
#include "Util.h"
#include <QRegularExpression>

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

    QRegularExpression re("(%[0-9]+)|([a-zA-Z0-9,\\.<>=\\+\\-\\*%/]+)");
    QRegularExpressionMatchIterator i = re.globalMatch(brick->getName());

    int x = MARGIN;
    int pos = 0;
    QList<Parameter> params = brick->getParams();
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.captured(1).length() > 0) {
            painter.setPen(pen);
            params[pos].paint(&painter, QPoint(x, VALUE_BRICK_MARGIN), widget->pos());
            x += params[pos++].size(Util::font()).width() + MARGIN;
        } else if (match.captured(2).length() > 0) {
            QString txt = match.captured(2).trimmed();
            painter.setPen(Util::textPen());
            painter.drawText(x, VALUE_BRICK_MARGIN + Util::textSize(txt, Util::font()).height(), txt);
            x += Util::textSize(txt, Util::font()).width() + MARGIN;
        }
    }
    painter.end();
}