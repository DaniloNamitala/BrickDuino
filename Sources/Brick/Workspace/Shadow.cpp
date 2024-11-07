#include "Shadow.h"
#include "FunctionBrickPainter.h"
#include "ValueBrickPainter.h"

Workspace::Shadow::Shadow(QWidget* parent, bool value) : Workspace::Brick(parent, "", QColor(0x5f5f5f)) {    
    if (value) {
        painter = new ValueBrickPainter();
        type = BrickType::VALUE;
    } else {
        painter = new FunctionBrickPainter();
        type = BrickType::FUNCTION;
    }

    //pen = QPen();
    //color.setAlpha(0x6F);
    //brush.setColor(color);
    this->_isShadow = true;
    recalculateSize();
}

BrickType Workspace::Shadow::getType() {
    return type;
}

int Workspace::Shadow::getWidth() {
    if (type == BrickType::VALUE)
        return EMPTY_VALUE_WIDTH;
    return 4 * BRICK_MIN_HEIGHT;
}

int Workspace::Shadow::getHeight() {
    if (type == BrickType::VALUE)
        return EMPTY_VALUE_HEIGHT;
    return Brick::getHeight();
}


void Workspace::Shadow::move(const QPoint& pos) {
    if (type == BrickType::VALUE)
        QWidget::move(pos);
    else
        Brick::move(pos);
}