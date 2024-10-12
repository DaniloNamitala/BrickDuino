#include "ToolboxFunctionBrick.h"
#include "FunctionBrickPainter.h"
#include <QDrag>

Toolbox::FunctionBrick::FunctionBrick(const char* name, QColor color) : Toolbox::Brick(name, color) {
    this->painter = new FunctionBrickPainter();
}

Toolbox::BrickType Toolbox::FunctionBrick::getType() {
    return Toolbox::BrickType::FUNCTION;
}