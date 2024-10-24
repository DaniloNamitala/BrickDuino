#pragma once

#include <QtCore>
#include <QtWidgets>
#include "PaintableBrick.h"

namespace Toolbox {
    enum BrickType {
        FUNCTION,
        STATEMENT,
        VALUE
    };
    class Brick : public PaintableBrick {
        public:
            Brick(const char* name, QColor color);

            void mouseMoveEvent(QMouseEvent* event) override;
            void mousePressEvent(QMouseEvent* event) override;
            void mouseReleaseEvent(QMouseEvent* event) override;
            
            virtual BrickType getType() = 0;
    };    
};
