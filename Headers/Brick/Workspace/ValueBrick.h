#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"
#include "WorkspaceBrick.h"	

namespace Workspace {
    class ValueBrick : public Workspace::Brick
    {
        protected:
            int getHeight() override;
            void recalculateSize() override;
            bool binary;
        public:
            ValueBrick(QWidget* parent, const char* name, QColor color, bool binary = false);
            ValueBrick(const char* name, QColor color, bool binary = false);
    };
};



