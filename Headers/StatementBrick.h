#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"
#include "Brick.h"	

#define EMPTY_STATEMENT_GAP 20
#define BRACKET_WIDTH 15

class StatementBrick : public Brick
{
    private:
        Brick* statementHead;
    
    
        int statementHeight();
    public:
        StatementBrick(QWidget* parent, const char* name, QColor color);
        int getHeight() override;
        int headerHeight();
        QPoint getStatementOrigin();
        void paintEvent(QPaintEvent* event) override;
        void insertBrick(Brick* brick);
        void removeBrick(Brick* brick);
        void move(const QPoint &pos);
};

