#include "ValueBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"
#include "ValueBrickPainter.h"

Workspace::ValueBrick::ValueBrick(QWidget* parent, const char* name, QColor color) : Workspace::Brick(parent, name, color) { 
    this->painter = new ValueBrickPainter();
    recalculateSize();
}

Workspace::ValueBrick::ValueBrick(const char* name, QColor color) : ValueBrick(nullptr, name, color) { }

int Workspace::ValueBrick::getWidth() { 
    return qMin(Brick::getWidth(), MIN_VALUE_WIDTH);
}

int Workspace::ValueBrick::getHeight() {
    int height = BRICK_MIN_HEIGHT;
    QFontMetrics fm(Util::font());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size(Util::font()).height());
    }
    height = qMax(height, fm.height());
    return height + 2 * VALUE_BRICK_MARGIN;
}

void Workspace::ValueBrick::move(const QPoint& pos) {
    QWidget::move(pos);
}

void Workspace::ValueBrick::recalculateSize() {
    int newW = getWidth();
    int newH = getHeight();

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);
}

BrickType Workspace::ValueBrick::getType() {
    return BrickType::VALUE;
}