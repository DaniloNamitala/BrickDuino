#include "Brick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"

Brick::Brick(const char* name, QColor color) {
    this->color = color;
    functionName = QString(name);
}

void Brick::paint(QPainter* painter, QPoint origin) {

}

void Brick::addParam(Parameter param) {
    params.append(param);
}

QColor Brick::getColor() {
    return color;
}

int Brick::width() { 
    QFontMetrics fm(Util::font());
    int funcNameWidth = fm.horizontalAdvance(functionName);
    int paramsWidth = 0;
    for (int i = 0; i < params.size(); i++) {
        paramsWidth += params[i].size(Util::font()).width();
    }
    int width = funcNameWidth + paramsWidth;

    // margins between function name, parameters and the edges
    width += params.size() * MARGIN + 2*MARGIN; 
    return width;
}

int Brick::height() { 
    int height = BRICK_MIN_HEIGHT;
    QFontMetrics fm(Util::font());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size(Util::font()).height());
    }
    height = qMax(height, fm.height());
    return height + 2*MARGIN;
}
