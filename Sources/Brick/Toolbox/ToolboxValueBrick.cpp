#include "ToolboxValueBrick.h"
#include "ValueBrickPainter.h"
#include "Util.h"

Toolbox::ValueBrick::ValueBrick(const char* name, QColor color) : Toolbox::Brick(name, color) {
    this->painter = new ValueBrickPainter();
    recalculateSize();
}

BrickType Toolbox::ValueBrick::getType() {
    return BrickType::VALUE;
}

int Toolbox::ValueBrick::getHeight() {
    int height = BRICK_MIN_HEIGHT;
    QFontMetrics fm(Util::font());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size(Util::font()).height());
    }
    height = qMax(height, fm.height());
    return height + 2 * VALUE_BRICK_MARGIN;
}

void Toolbox::ValueBrick::recalculateSize() {
    int newW = getWidth();
    int newH = getHeight();

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);
}