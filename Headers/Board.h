#pragma once

#include <QtCore>
#include <QtWidgets>
#include "WorkspaceBrick.h"


#define BOARD_BACKGROUND_COLOR QColor(0x1B1B1B)

class Board : public QWidget
{   
    private:
        QColor background;
        QPainter painter;
        QMap<int, QList<QWidget*>> zOrder;

        QList<Workspace::Brick*> bricks;
        Workspace::Brick* previewBrick;

    protected:
        void paintEvent(QPaintEvent* event) override;

        void dragMoveEvent(QDragMoveEvent* event) override;
        void dragEnterEvent(QDragEnterEvent* event) override;
        void dropEvent(QDropEvent* event) override;
        void dragLeaveEvent(QDragLeaveEvent* event) override;

    public:
        Board(QColor bgColor);
        ~Board();
        void setZOrder(QWidget* widget, int old_z, int new_z);
        void removeOrder(QWidget* widget, int z_order);
        void saveToFile(QString path);
};

