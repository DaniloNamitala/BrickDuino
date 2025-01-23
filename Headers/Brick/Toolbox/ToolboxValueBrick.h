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
            ValueType type;
        public:
            ValueBrick(const char* message, const char* name, QColor color, bool literal = false);
            ValueType setType(QString type);
            BrickType getType() override;
    };    
};
