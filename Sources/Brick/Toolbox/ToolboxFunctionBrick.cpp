#include "ToolboxFunctionBrick.h"
#include "FunctionBrickPainter.h"
#include <QDrag>

Toolbox::FunctionBrick::FunctionBrick(const char* message, const char* name, QColor color) : Toolbox::Brick(message, name, color) {
    this->painter = new FunctionBrickPainter();
}

BrickType Toolbox::FunctionBrick::getType() {
    return BrickType::FUNCTION;
}