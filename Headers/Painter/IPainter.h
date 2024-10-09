#pragma once

#include <QtCore>	
#include <QtWidgets>
#include "IPaintableBrick.h"

class IPainter {
    public:
        virtual void paint(IPaintableBrick* brick, QPaintEvent* event) = 0;
};