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
            ValueBrick(QWidget* parent, const char* message, const char* name, QColor color);
            ValueBrick(const char* message, const char* name, QColor color);
            BrickType getType() override;
            void move(const QPoint& pos) override;

            virtual void makeShadow(QPoint pos) override;
            virtual void removeShadow() override;
            virtual void replaceShadow(Brick* brick) override;
    };
};



