#include "ToolboxValueBrick.h"
#include "ValueBrickPainter.h"
#include "Util.h"

Toolbox::ValueBrick::ValueBrick(const char* message, const char* name, QColor color, bool literal) : Toolbox::Brick(message, name, color) {
    this->painter = new ValueBrickPainter();
    b_type = BrickType::VALUE;
    if (literal)
        b_type = BrickType::LITERAL_VALUE;
    recalculateSize();
}

BrickType Toolbox::ValueBrick::getType() {
    return b_type;
}

int Toolbox::ValueBrick::getHeight() {
    int height = BRICK_MIN_HEIGHT;
    QFontMetrics fm(Util::font_sm());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size().height());
    }
    height = qMax(height, fm.height());
    height += (params.count() == 0) ? (2 * VALUE_BRICK_MARGIN) : (2 * VALUE_BRICK_MARGIN_WITH_PARAM);
    return height;
}

void Toolbox::ValueBrick::recalculateSize() {
    int newW = getWidth();
    int newH = getHeight();

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);
}