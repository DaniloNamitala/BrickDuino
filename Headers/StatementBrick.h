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
        QList<Brick*> bricks;

    public:
        StatementBrick(const char* name, QColor color);
        void paint(QPainter* painter, QPoint origin) override;
        int height() override;
        int headerHeight();
        QPoint getStatementOrigin();

        void addBrick(Brick* brick);
};

