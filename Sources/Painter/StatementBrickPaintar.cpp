#include "StatementBrickPainter.h"
#include "Util.h"
#include <iostream>

void StatementBrickPainter::paint(IPaintableBrick* brick, QPaintEvent* event) {
    QPainterPath path;
    QWidget* widget = brick->getWidget();
    QPainter painter(widget);

    QFontMetrics fm(Util::font());
    QRegularExpression rx("(%[0-9]+)");

    QList<QString> lines = brick->getName().split("%s");
    lines.removeAll("");
    int statementIdx = 0;

    QPen pen = brick->getContourPen();

    // Draw the pin
    path.moveTo(2 * EDGE_RADIUS, PIN_H);
    path.arcTo(2 * EDGE_RADIUS, 0, 2 * PIN_H, 2 * PIN_H, 180, -180);
    
    // Desenha o lado direito da primeira linha
    path.lineTo(brick->getWidth() - 2 * EDGE_RADIUS, PIN_H);
    path.arcTo(brick->getWidth() - 2 * EDGE_RADIUS, PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    
    int lineBottom = PIN_H;
    for (QString line : lines) {

        int lineHeight = 2*MARGIN;
        QRegularExpressionMatchIterator i = rx.globalMatch(line);
        if (i.hasNext() && brick->getParams().count()) {
            lineHeight += qMax(fm.height(), brick->getParams()[0].size(Util::font()).height());
        } else {
            lineHeight += fm.height();
        }
        lineBottom += lineHeight;

        path.lineTo(brick->getWidth(), lineBottom - 2 * EDGE_RADIUS);
        
        if (statementIdx < brick->getStatements().count()) {
            int bottom = lineBottom + brick->getStatements()[statementIdx++].height();
            // Draw the socket
            path.arcTo(brick->getWidth() - 2 * EDGE_RADIUS, lineBottom - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);
            path.lineTo(BRACKET_WIDTH + 2 * EDGE_RADIUS + (PIN_H + pen.width()) * 2, lineBottom);
            path.arcTo(BRACKET_WIDTH + 2 * EDGE_RADIUS - pen.width(), lineBottom - (PIN_H + pen.width()), 2 * (PIN_H + pen.width()), 2 * (PIN_H + pen.width()), 0, 180);

            path.lineTo(BRACKET_WIDTH + EDGE_RADIUS, lineBottom);
            path.arcTo(BRACKET_WIDTH, lineBottom, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, 90);

            path.lineTo(BRACKET_WIDTH, bottom - EDGE_RADIUS);
            path.arcTo(BRACKET_WIDTH, bottom - 2*EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 180, 90);

            path.lineTo(brick->getWidth() - 2 * EDGE_RADIUS, bottom);
            path.arcTo(brick->getWidth() - 2 * EDGE_RADIUS, bottom, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
            lineBottom = bottom;
        }
    }

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

    int x = MARGIN;
    int y = PIN_H;
    statementIdx = 0;
    QList<Parameter> params = brick->getParams();
    for (QString line : lines) {
        int lineHeight = 2*MARGIN;
        QRegularExpressionMatchIterator i = rx.globalMatch(line);
        if (i.hasNext() && brick->getParams().count()) {
            lineHeight += qMax(fm.height(), brick->getParams()[0].size(Util::font()).height());
        } else {
            lineHeight += fm.height();
        }

        i = re.globalMatch(line);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            if (match.captured(1).length() > 0) {
                int pos = match.captured(1).mid(1).toInt() - 1;
                painter.setPen(pen);
                params[pos].paint(&painter, QPoint(x, y + MARGIN));
                x += params[pos].size(Util::font()).width() + MARGIN;
            } else if (match.captured(2).length() > 0) {
                QString txt = match.captured(2).trimmed();
                painter.setPen(Util::textPen());
                painter.drawText(x, y, fm.horizontalAdvance(line), lineHeight, Qt::AlignVCenter, txt);
                x += Util::textSize(txt, Util::font()).width() + MARGIN;
            }
        }
        y += lineHeight;
        if (statementIdx < brick->getStatements().count()) {
            y += brick->getStatements()[statementIdx].height();
        }
        x = MARGIN;
    }
    
    painter.end();
}