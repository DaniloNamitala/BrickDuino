#include "FunctionBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"
#include "FunctionBrickPainter.h"

Workspace::FunctionBrick::FunctionBrick(QWidget* parent, const char* message, const char* name, QColor color) : Workspace::Brick(parent, message, name, color) { 
    painter = new FunctionBrickPainter();
}

Workspace::FunctionBrick::FunctionBrick(const char* message, const char* name, QColor color) : FunctionBrick(nullptr, message, name, color) { }

BrickType Workspace::FunctionBrick::getType() {
    return BrickType::FUNCTION;
}