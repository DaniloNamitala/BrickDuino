#include "Board.h"

#include "FunctionBrick.h"
#include "Parameter.h"
#include "Shadow.h"
#include "StatementBrick.h"


Board::Board(QColor bgColor) {
    background = bgColor;
    setMouseTracking(true);
}

void Board::paintEvent(QPaintEvent* event) {
    painter.begin(this);
    painter.fillRect(event->rect(), background);
    painter.end();
}

void Board::removeOrder(QWidget* widget, int z_order) {
    if (zOrder.contains(z_order)) {
        zOrder[z_order].removeAll(widget);
    }
}

void Board::setZOrder(QWidget* widget, int old_z, int new_z) {
    if (old_z == new_z) return;

    if (zOrder.contains(old_z)) {
        zOrder[old_z].removeAll(widget);
        if (zOrder[old_z].isEmpty()) 
            zOrder.remove(old_z);
    }

    if (!zOrder.contains(new_z)) zOrder[new_z] = QList<QWidget*>();
    zOrder[new_z].append(widget);

    QMapIterator<int, QList<QWidget*>> i(zOrder);
    while (i.hasNext()) {
        i.next();
        for (QWidget* w : i.value()) {
            w->raise();
        }
    }
}