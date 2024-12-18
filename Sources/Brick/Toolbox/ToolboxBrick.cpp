#include "ToolboxBrick.h"
#include "FunctionBrickPainter.h"
#include <QDrag>

Toolbox::Brick::Brick(const char* message, const char* name, QColor color) : PaintableBrick(nullptr, message, name, color) {
    this->painter = new FunctionBrickPainter();
    setMouseTracking(true);
}


void Toolbox::Brick::mousePressEvent(QMouseEvent* event) {
    // set mouse cursor to closed hand
    setCursor(Qt::ClosedHandCursor);
    if (event->buttons() & Qt::LeftButton) {
        QDrag* drag = new QDrag(this);
        QMimeData* mimeData = new QMimeData();
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        
        stream << message;
        stream << name;
        stream << getType();
        stream << color;

        for (Parameter param : this->getParams()) {
            stream << param.getType();
            stream << param.getName();
        }

        mimeData->setData("application/x-brick", data);
        drag->setMimeData(mimeData);
        drag->exec(Qt::CopyAction);
    }
}

void Toolbox::Brick::mouseReleaseEvent(QMouseEvent* event) {
    // set mouse cursor to open hand
    setCursor(Qt::OpenHandCursor);
}


void Toolbox::Brick::mouseMoveEvent(QMouseEvent* event) {
    // set mouse cursor to open hand
    setCursor(Qt::OpenHandCursor);
}