#include "Shadow.h"
#include "FunctionBrickPainter.h"
#include "ValueBrickPainter.h"

Workspace::Shadow::Shadow(QWidget* parent) : Workspace::Brick(parent, "", QColor(0x5f5f5f)) {    
    painter = new FunctionBrickPainter();
    type = BrickType::FUNCTION;

    pen = QPen();
    color.setAlpha(0x6F);
    brush.setColor(color);
    this->_isShadow = true;
    recalculateSize();
}
int Workspace::Shadow::getWidth() {
    if (type == BrickType::VALUE)
        return EMPTY_VALUE_WIDTH;
    return 4 * BRICK_MIN_HEIGHT;
}