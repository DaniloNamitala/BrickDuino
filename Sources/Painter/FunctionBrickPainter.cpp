#include "FunctionBrickPainter.h"
#include "Util.h"
#include "Parameter.h"

void FunctionBrickPainter::paint(IPaintableBrick* brick, QPaintEvent* event) {
    QPainterPath path;
    QWidget* widget = brick->getWidget();

    QPen pen = brick->getContourPen();
    QFontMetrics fm(Util::font());

    QPixmap** cache = brick->getCache();
    if (*cache != nullptr) {
        QPainter _painter(widget);
        _painter.drawPixmap(widget->rect(), *(*cache));
        _painter.end();
        return;
    }
    
    *cache = new QPixmap(widget->size());
    (*cache)->fill(Qt::transparent);
    QPainter painter(*cache);

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

    QRegularExpression re("(%[0-9]+)|([a-zA-Z0-9,\\.<>=\\+\\-\\*%/]+)");
    QRegularExpressionMatchIterator i = re.globalMatch(brick->getName());

    int x = MARGIN;
    int pos = 0;
    QList<Parameter>& params = brick->getParams();
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.captured(1).length() > 0) {
            painter.setPen(pen);
            int y = (brick->getHeight() - params[pos].size().height()) / 2;
            params[pos].paint(&painter, QPoint(x, y + PIN_H), widget->pos());
            x += params[pos++].size().width() + MARGIN;
        } else if (match.captured(2).length() > 0) {
            QString txt = match.captured(2).trimmed();
            painter.setPen(Util::textPen());
            painter.drawText(x, PIN_H, fm.horizontalAdvance(txt), brick->getHeight(), Qt::AlignVCenter, txt);
            x += Util::textSize(txt, Util::font()).width() + MARGIN;
        }
    }

    painter.end();
    QPainter _painter(widget);
    _painter.drawPixmap(widget->rect(), *(*cache));
    _painter.end();
}