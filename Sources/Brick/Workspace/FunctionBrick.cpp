#include "FunctionBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"
#include "FunctionBrickPainter.h"

Workspace::FunctionBrick::FunctionBrick(QWidget* parent, const char* name, QColor color) : Workspace::Brick(parent, name, color) { 
    painter = new FunctionBrickPainter();
}

Workspace::FunctionBrick::FunctionBrick(const char* name, QColor color) : FunctionBrick(nullptr, name, color) { }

BrickType Workspace::FunctionBrick::getType() {
    return BrickType::FUNCTION;
}