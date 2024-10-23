#include "PaintableBrick.h"
#include "Util.h"

PaintableBrick::PaintableBrick(QWidget* parent, const char* name, QColor color): QWidget(parent) {
    this->color = color;
    this->pen = QPen(color.darker(CONTOUR_COLOR_DARKER));
    this->name = name;
    pen.setWidth(2);
    recalculateSize();
}

QPen PaintableBrick::getContourPen() { return pen; }

QList<Parameter> PaintableBrick::getParams() { return params; }

QList<Statement> PaintableBrick::getStatements() { return statements; }

QString PaintableBrick::getName() { return name; }

QWidget* PaintableBrick::getWidget() { return (QWidget*) this; }

QColor PaintableBrick::getColor() { return color; }

void PaintableBrick::paintEvent(QPaintEvent* event) {
    painter->paint(this, event);
}

void PaintableBrick::recalculateSize() {
    int newW = getWidth();
    int newH = getHeight() + PIN_H;

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);
}

int PaintableBrick::getWidth() {
    QFontMetrics fm(Util::font());
    
    QRegularExpression re("(%[0-9]+)|([a-zA-Z0-9,\\.<>= ]+)");
    QRegularExpressionMatchIterator i = re.globalMatch(getName());

    int width = MARGIN;
    int pos = 0;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.captured(1).length() > 0) {
            if (params.count() > pos)
                width += params[pos++].size(Util::font()).width() + MARGIN;
        } else if (match.captured(2).length() > 0) {
            QString txt = match.captured(2).trimmed();
            width += fm.horizontalAdvance(txt) + MARGIN;
        }
    }
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