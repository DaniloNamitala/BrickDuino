#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"
#include "WorkspaceBrick.h"	
#include "Statement.h"

namespace Workspace {

    class StatementBrick : public Workspace::Brick
    {
        private:
            Workspace::Brick* statementHead;
            int statementHeight();
        public:
            StatementBrick(QWidget* parent, const char* name, QColor color);
            StatementBrick(const char* name, QColor color);
            int getHeight() override;
            int headerHeight() override;
            QPoint getStatementOrigin();
            void insertBrick(Workspace::Brick* brick);
            void removeBrick(Workspace::Brick* brick);
            void move(const QPoint &pos);
            void setZOrder(int z);

            void makeShadow(QPoint pos) override;
            void removeShadow() override;
            void replaceShadow(Workspace::Brick* brick);
    };
};