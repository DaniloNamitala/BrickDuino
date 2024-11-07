#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"
#include "WorkspaceBrick.h"	
#include "Statement.h"
#include <QPushButton>

namespace Workspace {

    class StatementBrick : public Workspace::Brick
    {
        private: 
            int shadow_statement_idx;

            QPushButton* btnConfig;
        protected:
            void openConfig() override;
        public:
            StatementBrick(QWidget* parent, const char* name, QColor color);
            StatementBrick(const char* name, QColor color);
            void insertBrick(Workspace::Brick* brick, int st_idx);
            void removeBrick(Workspace::Brick* brick);
            void move(const QPoint &pos);
            void setZOrder(int z);

            void makeShadow(QPoint pos, bool value) override;
            void removeShadow() override;
            void replaceShadow(Workspace::Brick* brick);
            
            void recalculateSize() override;
            void addCondition();
            void removeCondition();

            void addElse();
            void removeElse();
            BrickType getType() override;
    };
};