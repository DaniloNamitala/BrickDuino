#include "Shadow.h"

Shadow::Shadow(QWidget* parent) : FunctionBrick(parent, "", QColor(0x5f5f5f)) {    
    contourPen = QPen();
    color.setAlpha(0x6F);
    brush.setColor(color);
    this->_isShadow = true;
    recalculateSize();
}

int Shadow::getWidth() {
    return 6 * BRICK_MIN_HEIGHT;
}
