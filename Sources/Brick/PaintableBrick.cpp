#include "PaintableBrick.h"
#include "Util.h"

PaintableBrick::PaintableBrick(QWidget* parent, const char* name, QColor color): QWidget(parent) {
    this->color = color;
    this->pen = QPen(color.darker(CONTOUR_COLOR_DARKER));
    this->name = name;
    pen.setWidth(2);
}

QPen PaintableBrick::getContourPen() { return pen; }

QList<Parameter> PaintableBrick::getParams() { return params; }

QString PaintableBrick::getName() { return name; }

QWidget* PaintableBrick::getWidget() { return (QWidget*) this; }

QColor PaintableBrick::getColor() { return color; }

void PaintableBrick::paintEvent(QPaintEvent* event) {
    painter->paint(this, event);
}

void PaintableBrick::recalculateSize() {
    int h = height();
    int newW = getWidth();
    int newH = getHeight() + PIN_H;

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);
}

int PaintableBrick::getWidth() {
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

int PaintableBrick::getHeight() {
    int height = BRICK_MIN_HEIGHT;
    QFontMetrics fm(Util::font());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size(Util::font()).height());
    }
    height = qMax(height, fm.height());
    return height + 2 * MARGIN;
}

void PaintableBrick::addParam(Parameter param) {
    params.append(param);
    recalculateSize();
}

int PaintableBrick::headerHeight() { return 0; }