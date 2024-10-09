#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"
#include "Brick.h"	
#include "FunctionBrickPainter.h"

class FunctionBrick : public Brick
{
    private:
        IPainter* painter;
    public:
        FunctionBrick(QWidget* parent, const char* name, QColor color);
        FunctionBrick(const char* name, QColor color);
        void paintEvent(QPaintEvent* event) override;
};

