#include "ToolboxBrick.h"
#include "Util.h"
#include "FunctionBrickPainter.h"

ToolboxBrick::ToolboxBrick(const char* name, QColor color) : QWidget() {
    this->color = color;
    this->contourPen = QPen(color.darker(CONTOUR_COLOR_DARKER));
    this->name = QString(name);
    this->painter = new FunctionBrickPainter();

    
    contourPen.setWidth(2);
}

void ToolboxBrick::paintEvent(QPaintEvent* event) {
    painter->paint(this, event);
}

void ToolboxBrick::recalculateSize() {
    int h = height();
    int newW = getWidth();
    int newH = getHeight() + PIN_H;

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);
}

int ToolboxBrick::getWidth() {
    QFontMetrics fm(Util::font());
    int funcNameWidth = fm.horizontalAdvance(name);
    int paramsWidth = 0;
    for (int i = 0; i < params.size(); i++) {
        paramsWidth += params[i].size(Util::font()).width();
    }
    int width = funcNameWidth + paramsWidth;

    // margins between function name, parameters and the edges
    width += params.size() * MARGIN + 2 * MARGIN;
    return width;
}

int ToolboxBrick::getHeight() {
    int height = BRICK_MIN_HEIGHT;
    QFontMetrics fm(Util::font());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size(Util::font()).height());
    }
    height = qMax(height, fm.height());
    return height + 2 * MARGIN;
}

void ToolboxBrick::addParam(Parameter param) {
    params.append(param);
    recalculateSize();
}

QPen ToolboxBrick::getContourPen() { return contourPen; }

QList<Parameter> ToolboxBrick::getParams() { return params; }

QString ToolboxBrick::getName() { return name; }

QWidget* ToolboxBrick::getWidget() { return (QWidget*) this; }

QColor ToolboxBrick::getColor() { return color; }
