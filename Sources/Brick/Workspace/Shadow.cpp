#include "Shadow.h"

Workspace::Shadow::Shadow(QWidget* parent) : Workspace::FunctionBrick(parent, "", QColor(0x5f5f5f)) {    
    pen = QPen();
    color.setAlpha(0x6F);
    brush.setColor(color);
    this->_isShadow = true;
    recalculateSize();
}

int Workspace::Shadow::getWidth() {
    return 4 * BRICK_MIN_HEIGHT;
}