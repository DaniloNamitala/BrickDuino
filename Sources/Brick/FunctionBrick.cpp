#include "FunctionBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"

FunctionBrick::FunctionBrick(QWidget* parent, const char* name, QColor color) : Brick(parent, name, color) { 
    painter = new FunctionBrickPainter();
}

FunctionBrick::FunctionBrick(const char* name, QColor color) : FunctionBrick(nullptr, name, color) { }

void FunctionBrick::paintEvent(QPaintEvent* event) {
    painter->paint(this, event);
}