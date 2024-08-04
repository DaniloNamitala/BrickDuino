#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Brick.h"

class Board : public QWidget
{   
    private:
        QColor background;
        QPainter painter;

        QList<Brick*> bricks;
    public:
        Board(QColor bgColor);
    protected:
        void paintEvent(QPaintEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;

};