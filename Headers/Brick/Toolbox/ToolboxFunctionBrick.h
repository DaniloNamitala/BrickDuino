#pragma once

#include <QtCore>
#include <QtWidgets>
#include "ToolboxBrick.h"

namespace Toolbox {
    class FunctionBrick : public Brick {
        public:
            FunctionBrick(const char* message, const char* name, QColor color);
            BrickType getType() override;
    };    
};
