#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"
#include "Brick.h"	

class FunctionBrick : public Brick
{
    public:
        FunctionBrick(QWidget* parent, const char* name, QColor color);
        void paintEvent(QPaintEvent* event) override;
};

