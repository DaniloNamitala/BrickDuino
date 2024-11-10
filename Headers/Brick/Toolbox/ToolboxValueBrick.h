#pragma once

#include <QtCore>
#include <QtWidgets>
#include "ToolboxBrick.h"

namespace Toolbox {
    class ValueBrick : public Brick {
        protected:
            int getHeight() override;
            void recalculateSize() override;
            bool binary;
        public:
            ValueBrick(const char* message, const char* name, QColor color);
            BrickType getType() override;
    };    
};
