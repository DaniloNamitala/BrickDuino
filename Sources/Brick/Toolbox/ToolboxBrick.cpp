#include "ToolboxBrick.h"
#include "FunctionBrickPainter.h"
#include <QDrag>

Toolbox::Brick::Brick(const char* name, QColor color) : PaintableBrick(nullptr, name, color) {
    this->painter = new FunctionBrickPainter();
}


void Toolbox::Brick::mousePressEvent(QMouseEvent* event) {
    // set mouse cursor to closed hand
    setCursor(Qt::ClosedHandCursor);
}

void Toolbox::Brick::mouseReleaseEvent(QMouseEvent* event) {
    // set mouse cursor to open hand
    setCursor(Qt::OpenHandCursor);
}


void Toolbox::Brick::mouseMoveEvent(QMouseEvent* event) {
    // set mouse cursor to open hand
    setCursor(Qt::OpenHandCursor);
    if (event->buttons() & Qt::LeftButton) {
        QDrag* drag = new QDrag(this);
        QMimeData* mimeData = new QMimeData();
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << this->getName();
        mimeData->setData("application/x-brick", data);
        drag->setMimeData(mimeData);
        drag->exec(Qt::CopyAction);
    }
}