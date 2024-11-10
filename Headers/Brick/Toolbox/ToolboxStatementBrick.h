#pragma once

#include <QtCore>
#include <QtWidgets>
#include "ToolboxBrick.h"
#include "Statement.h"

namespace Toolbox {
    class StatementBrick : public Toolbox::Brick {
        public:
            StatementBrick(const char* message, const char* name, QColor color);
            BrickType getType() override;
    };    
};
