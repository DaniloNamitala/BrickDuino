#pragma once

#include <QtCore>	
#include <QtWidgets>
#include "IPaintableBrick.h"

#define MARGIN 8
#define PIN_H 5
#define EDGE_RADIUS 6
#define BRICK_MIN_HEIGHT 20
#define CONTOUR_COLOR_DARKER 300

#define EMPTY_STATEMENT_GAP 20
#define BRACKET_WIDTH 15



class IPainter {
    public:
        virtual void paint(IPaintableBrick* brick, QPaintEvent* event) = 0;
};