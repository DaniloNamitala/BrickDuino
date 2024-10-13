#include "StatementBrickPainter.h"
#include "Util.h"

void StatementBrickPainter::paint(IPaintableBrick* brick, QPaintEvent* event) {
    QPainterPath path;
    QWidget* widget = brick->getWidget();
    QPainter painter(widget);

    QPen pen = brick->getContourPen();

        // Draw the pin
    path.moveTo(2 * EDGE_RADIUS, PIN_H);
    path.arcTo(2 * EDGE_RADIUS, 0, 2 * PIN_H, 2 * PIN_H, 180, -180);

    // Draw the right corners
    path.lineTo(brick->getWidth() - 2 * EDGE_RADIUS, PIN_H);
    path.arcTo(brick->getWidth() - 2 * EDGE_RADIUS, PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    path.lineTo(brick->getWidth(), brick->headerHeight() - 2 * EDGE_RADIUS + PIN_H);
    path.arcTo(brick->getWidth() - 2 * EDGE_RADIUS, brick->headerHeight() - 2 * EDGE_RADIUS + PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);

    // Draw the socket
    path.lineTo(BRACKET_WIDTH + 2 * EDGE_RADIUS + (PIN_H + pen.width()) * 2, brick->headerHeight() + PIN_H);
    path.arcTo(BRACKET_WIDTH + 2 * EDGE_RADIUS - pen.width(), brick->headerHeight() - (PIN_H + pen.width()) + PIN_H, 2 * (PIN_H + pen.width()), 2 * (PIN_H + pen.width()), 0, 180);

    path.lineTo(BRACKET_WIDTH + EDGE_RADIUS, brick->headerHeight() + PIN_H);
    path.arcTo(BRACKET_WIDTH, brick->headerHeight() + PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, 90);

    path.lineTo(BRACKET_WIDTH, widget->height() - BRACKET_WIDTH - EDGE_RADIUS);
    path.arcTo(BRACKET_WIDTH, widget->height() - BRACKET_WIDTH - 2*EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 180, 90);

    
    path.lineTo(brick->getWidth() - 2 * EDGE_RADIUS, widget->height() - BRACKET_WIDTH);
    path.arcTo(brick->getWidth() - 2 * EDGE_RADIUS, widget->height() - BRACKET_WIDTH, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    path.lineTo(brick->getWidth(), widget->height() - 2 * EDGE_RADIUS);
    path.arcTo(brick->getWidth() - 2 * EDGE_RADIUS, widget->height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);

    // Draw the socket
    path.lineTo(2 * EDGE_RADIUS + (PIN_H + pen.width()) * 2, widget->height());
    path.arcTo(2 * EDGE_RADIUS - pen.width(), widget->height() - (PIN_H + pen.width()), 2 * (PIN_H + pen.width()), 2 * (PIN_H + pen.width()), 0, 180);

    // Draw the bottom left corner
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
    QList<Parameter> params = brick->getParams();
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.captured(1).length() > 0) {
            painter.setPen(pen);
            params[pos].paint(&painter, QPoint(x, MARGIN + PIN_H));
            x += params[pos++].size(Util::font()).width() + MARGIN;
        } else if (match.captured(2).length() > 0) {
            QString txt = match.captured(2).trimmed();
            painter.setPen(Util::textPen());
            painter.drawText(x, MARGIN + Util::textSize(txt, Util::font()).height() + PIN_H, txt);
            x += Util::textSize(txt, Util::font()).width() + MARGIN;
        }
    }
    painter.end();
}