#pragma once

#include <QtCore>
#include <QtWidgets>
#include "IPaintableBrick.h"
#include "IPainter.h"

class ValueBrickPainter : public IPainter {
    public:
        void paint(IPaintableBrick* brick, QPaintEvent* event) override;
};