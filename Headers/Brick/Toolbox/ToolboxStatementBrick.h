#pragma once

#include <QtCore>
#include <QtWidgets>
#include "ToolboxBrick.h"

namespace Toolbox {
    class StatementBrick : public Toolbox::Brick {
        public:
            StatementBrick(const char* name, QColor color);
            int getHeight() override;
            int headerHeight() override;
    };    
};
