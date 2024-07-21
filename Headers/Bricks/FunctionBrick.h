#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"
#include "Brick.h"	

class FunctionBrick : public Brick
{
    public:
        FunctionBrick(const char* name, QColor color);
        void paint(QPainter* painter, QPoint origin) override;
};

