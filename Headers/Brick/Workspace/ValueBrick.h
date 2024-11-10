#pragma once

#include <QtCore>
#include <QtWidgets>
#include "WorkspaceBrick.h"	

namespace Workspace {
    class ValueBrick : public Workspace::Brick
    {
        protected:
            int getHeight() override;
            void recalculateSize() override;
        public:
            ValueBrick(QWidget* parent, const char* name, QColor color);
            ValueBrick(const char* name, QColor color);
            BrickType getType() override;
            void move(const QPoint& pos) override;
    };
};



