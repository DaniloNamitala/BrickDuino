#pragma once

#include <QtCore>
#include <QtWidgets>
#include "IPaintableBrick.h"
#include "IPainter.h"

class StatementBrickPainter : public IPainter {
    public:
        void paint(IPaintableBrick* brick, QPaintEvent* event) override;
};