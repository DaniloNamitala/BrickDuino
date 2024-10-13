#include "ValueBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"
#include "ValueBrickPainter.h"
#include "BinaryOperatorPainter.h"

Workspace::ValueBrick::ValueBrick(QWidget* parent, const char* name, QColor color, bool binary) : Workspace::Brick(parent, name, color) { 
    this->binary = binary;
    this->painter = binary ? (IPainter*)new BinaryOperatorPainter() : (IPainter*)new ValueBrickPainter();
    recalculateSize();
}

Workspace::ValueBrick::ValueBrick(const char* name, QColor color, bool binary) : ValueBrick(nullptr, name, color, binary) { }

int Workspace::ValueBrick::getHeight() {
    int height = BRICK_MIN_HEIGHT;
    QFontMetrics fm(Util::font());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size(Util::font()).height());
    }
    height = qMax(height, fm.height());
    return height + 2 * VALUE_BRICK_MARGIN;
}

void Workspace::ValueBrick::recalculateSize() {
    int newW = getWidth();
    int newH = getHeight();

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);
}