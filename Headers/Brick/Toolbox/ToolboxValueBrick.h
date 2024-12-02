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
            BrickType b_type;
        public:
            ValueBrick(const char* message, const char* name, QColor color, bool literal = false);
            BrickType getType() override;
    };    
};
