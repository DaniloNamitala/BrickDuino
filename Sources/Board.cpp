#include "Board.h"

#include "FunctionBrick.h"
#include "Parameter.h"
#include "Shadow.h"
#include "StatementBrick.h"

Board::Board(QColor bgColor) {
    background = bgColor;
    setMouseTracking(true);

    Brick* b1 = new FunctionBrick(this, "Analog Write", QColor(0, 128, 0));
    b1->addParam(Parameter(ValueType::STRING));
    bricks.append(b1);

    Brick* b2 = new FunctionBrick(this, "Analog Read", QColor(0, 128, 0));
    b2->addParam(Parameter(ValueType::STRING));
    bricks.append(b2);
    b1->attach(b2);

    Brick* b3 = new FunctionBrick(this, "Escreva no Serial", QColor(0, 128, 0));
    b3->addParam(Parameter(ValueType::STRING));
    bricks.append(b3);
    b2->attach(b3);

    StatementBrick* b4 =
        new StatementBrick(this, "Loop", QColor(0, 128, 0));
    b4->addParam(Parameter(ValueType::STRING));
    b4->move(QPoint(10, 10));
    bricks.append(b4);
    b4->insertBrick(b1);
    b4->setZOrder(0);

    Brick* b5 = new FunctionBrick(this, "Escreva no Serial", QColor(0, 128, 0));
    b4->move(QPoint(200, 50));
    b5->addParam(Parameter(ValueType::STRING));
    bricks.append(b5);
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