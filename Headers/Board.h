#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Brick.h"


#define BOARD_BACKGROUND_COLOR QColor(0x1B1B1B)

class Board : public QWidget
{   
    private:
        QColor background;
        QPainter painter;
        QMap<int, QList<QWidget*>> zOrder;

        QList<Brick*> bricks;
    public:
        Board(QColor bgColor);
        void setZOrder(QWidget* widget, int old_z, int new_z);
        void removeOrder(QWidget* widget, int z_order);
    protected:
        void paintEvent(QPaintEvent* event) override;

};

