#include "Brick.h"

#include <QCursor>
#include <QPainter>
#include <QPainterPath>

#include "Board.h"
#include "StatementBrick.h"
#include "Util.h"

Brick::Brick(QWidget* parent, const char* name, QColor color)
    : QWidget(parent) {
    this->color = color;
    this->contourPen = QPen(color.darker(CONTOUR_COLOR_DARKER));
    this->functionName = QString(name);
    this->owner = nullptr;
    this->next = nullptr;
    this->previous = nullptr;

    setMouseTracking(true);
    recalculateSize();
    contourPen.setWidth(2);
}

void Brick::addParam(Parameter param) {
    params.append(param);
    recalculateSize();
}

QColor Brick::getColor() { return color; }

int Brick::getWidth() {
    QFontMetrics fm(Util::font());
    int funcNameWidth = fm.horizontalAdvance(functionName);
    int paramsWidth = 0;
    for (int i = 0; i < params.size(); i++) {
        paramsWidth += params[i].size(Util::font()).width();
    }
    int width = funcNameWidth + paramsWidth;

    // margins between function name, parameters and the edges
    width += params.size() * MARGIN + 2 * MARGIN;
    return width;
}

int Brick::getHeight() {
    int height = BRICK_MIN_HEIGHT;
    QFontMetrics fm(Util::font());
    for (int i = 0; i < params.size(); i++) {
        height = qMax(height, params[i].size(Util::font()).height());
    }
    height = qMax(height, fm.height());
    return height + 2 * MARGIN;
}

void Brick::mousePressEvent(QMouseEvent* event) { mousePos = event->pos(); }

void Brick::mouseReleaseEvent(QMouseEvent* event) {
    setCursor(QCursor(Qt::OpenHandCursor));
}

void Brick::mouseMoveEvent(QMouseEvent* event) {
    setCursor(QCursor(Qt::OpenHandCursor));
    if (event->buttons() & Qt::LeftButton) {
        raise();
        setCursor(QCursor(Qt::ClosedHandCursor));
        QPoint newPos = mapToParent(event->pos()) - mousePos;

        if (previous != nullptr) previous->dettach(this);

        move(newPos);

        if (owner != nullptr) {
            ((StatementBrick*)owner)->removeBrick(this);
            setOwner(nullptr);
        }
    }
}

void Brick::setPrevious(Brick* brick) { this->previous = brick; }

void Brick::attach(Brick* brick) {
    this->next = brick;
    brick->setPrevious(this);
    brick->setOwner(owner);

    QPoint p = this->pos();
    p.setY(p.y() + this->height());
    brick->move(p);
}

void Brick::dettach(Brick* brick) {
    this->next = nullptr;
    brick->setPrevious(nullptr);
}

void Brick::setOwner(StatementBrick* owner) { 
    this->owner = owner; 
    if (next != nullptr) next->setOwner(owner);
}

void Brick::recalculateSize() {
    int h = height();
    resize(getWidth(), getHeight() + PIN_H);
    if (owner != nullptr) {
        owner->recalculateSize();
    }
    if (h != height() && next != nullptr) {
        QPoint p = this->pos();
        p.setY(p.y() + this->height());
        next->move(p);
    }
}

void Brick::move(const QPoint& pos) {
    QPoint p(pos.x(), pos.y() - PIN_H);
    QWidget::move(p);

    if (next != nullptr) {
        p.setY(p.y() + this->height());
        next->move(p);
    }
}