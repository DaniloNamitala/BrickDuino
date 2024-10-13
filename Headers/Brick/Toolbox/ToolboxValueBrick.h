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
            ValueBrick(const char* name, QColor color, bool binary = false);
            BrickType getType() override;
    };    
};
