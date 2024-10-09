#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Brick.h"
#include "IPainter.h"

class FunctionBrickPainter : public IPainter {
    public:
        void paint(IPaintableBrick* brick, QPaintEvent* event) override;
};