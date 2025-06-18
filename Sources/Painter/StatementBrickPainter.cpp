#include "StatementBrickPainter.h"
#include "Util.h"
#include <iostream>

void StatementBrickPainter::paint(IPaintableBrick* brick, QPaintEvent* event) {
    QPainterPath path;
    QWidget* widget = brick->getWidget();

    QFontMetrics fm(Util::font());
    QRegularExpression rx("(%[0-9]+)");

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

    int statementIdx = 0;
    QPen pen = brick->getContourPen();
    // Draw the pin
    path.moveTo(2 * EDGE_RADIUS, PIN_H);
    path.arcTo(2 * EDGE_RADIUS, 0, 2 * PIN_H, 2 * PIN_H, 180, -180);
    
    // Desenha o lado direito da primeira linha
    path.lineTo(brick->getWidth() - 2 * EDGE_RADIUS, PIN_H);
    path.arcTo(brick->getWidth() - 2 * EDGE_RADIUS, PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    
    int lineBottom = PIN_H;
    for (int i = 0; i < brick->getLines().count(); i++) {
        lineBottom += brick->headerSize(i).height();

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

    QList<Parameter>& params = brick->getParams();
    for (int i = 0; i < brick->getLines().count(); i++) {
        QString line = brick->getLines().at(i);

        if (line.contains("%v0"))
            line.replace("%v0", brick->getVariableName());

        int lineHeight = brick->headerSize(i).height();

        QRegularExpressionMatchIterator it = re.globalMatch(line);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            if (match.captured(1).length() > 0) { // pinta parametro
                int pos = match.captured(1).mid(1).toInt() - 1;
                painter.setPen(pen);
                int _deltaY = (lineHeight - params[pos].size().height()) / 2;
                params[pos].paint(&painter, QPoint(x, y + _deltaY), widget->pos());
                x += params[pos].size().width() + MARGIN;
            } else if (match.captured(2).length() > 0) { // pinta texto
                QString txt = match.captured(2).trimmed();
                painter.setPen(Util::textPen());
                painter.drawText(x, y, fm.horizontalAdvance(line), lineHeight, Qt::AlignVCenter, txt);
                x += Util::textSize(txt, Util::font()).width() + MARGIN;
            }
        }
        y += lineHeight;
        if (statementIdx < brick->getStatements().count()) {
            y += brick->getStatements()[statementIdx++].height();
        }
        x = MARGIN;
    }

    if (brick->showConfig()) {
        // paint config icon
        QPixmap bmp("D:/Projetos/TCC/ShafraBlock/Assets/config.png", "png");
        painter.drawPixmap(brick->configRect(), bmp);
    }
    
    painter.end();
    QPainter _painter(widget);
    _painter.drawPixmap(widget->rect(), *(*cache));
    _painter.end();
}