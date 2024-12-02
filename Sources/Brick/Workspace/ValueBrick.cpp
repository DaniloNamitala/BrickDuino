
#include "ValueBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"
#include "ValueBrickPainter.h"

Workspace::ValueBrick::ValueBrick(QWidget* parent, const char* message, const char* name, QColor color) : Workspace::Brick(parent, message, name, color) { 
    this->painter = new ValueBrickPainter();
    recalculateSize();
}

Workspace::ValueBrick::ValueBrick(const char* message, const char* name, QColor color) : ValueBrick(nullptr, message, name, color) { }

int Workspace::ValueBrick::getHeight() {
    int height = BRICK_MIN_HEIGHT;
    QFontMetrics fm(Util::font_sm());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size().height());
    }
    height = qMax(height, fm.height());
    height += (params.count() == 0) ? (2 * VALUE_BRICK_MARGIN) : (2 * VALUE_BRICK_MARGIN_WITH_PARAM);
    return height;
}

void Workspace::ValueBrick::move(const QPoint& pos) {
    QWidget::move(pos);
    for (int i=0; i< params.count(); i++) {
        params[i].reposition(pos);
    }
}

void Workspace::ValueBrick::recalculateSize() {
    int newW = getWidth();
    int newH = getHeight();

    if (*cachePaint != nullptr)
        delete *cachePaint;
    *cachePaint = nullptr;

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);
    
    if (owner != nullptr) {
        owner->recalculateSize();
    }
    update();
}

BrickType Workspace::ValueBrick::getType() {
    return BrickType::VALUE;
}