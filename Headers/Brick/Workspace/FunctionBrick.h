#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"
#include "WorkspaceBrick.h"	

namespace Workspace {
    class FunctionBrick : public Workspace::Brick
    {
        public:
            FunctionBrick(QWidget* parent, const char* name, QColor color);
            FunctionBrick(const char* name, QColor color);
            void paintEvent(QPaintEvent* event) override;
    };
};



