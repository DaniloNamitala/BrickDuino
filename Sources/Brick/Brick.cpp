#include "Brick.h"

#include <QCursor>
#include <QPainter>
#include <QPainterPath>

#include "Board.h"
#include "Shadow.h"
#include "StatementBrick.h"
#include "Util.h"

#include <iostream>

Brick::Brick(QWidget* parent, const char* name, QColor color)
    : QWidget(parent) {
    this->z_order = -1;
    this->color = color;
    this->contourPen = QPen(color.darker(CONTOUR_COLOR_DARKER));
    this->functionName = QString(name);
    this->owner = nullptr;
    this->next = nullptr;
    this->previous = nullptr;
    this->shadow = nullptr;
    this->lastCloser = nullptr;
    this->_isShadow = false;

    setMouseTracking(true);
    recalculateSize();
    contourPen.setWidth(2);
    show();
}

Brick::Brick(const char* name, QColor color) : Brick(nullptr, name, color) { }

void Brick::setColor(QColor color) {
    this->color = color;
    update();
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
    if (lastCloser != nullptr) {
        lastCloser->replaceShadow(this);
    }
    lastCloser = nullptr;
    setZOrder(0);
}

void Brick::replaceShadow(Brick* brick){
    removeShadow();
    attach(brick);
}

void Brick::mouseMoveEvent(QMouseEvent* event) {
    setCursor(QCursor(Qt::OpenHandCursor));

    if (event->buttons() & Qt::LeftButton) {
        setZOrder(INT32_MAX);
        setCursor(QCursor(Qt::ClosedHandCursor));
        QPoint newPos = mapToParent(event->pos()) - mousePos;

        if (previous != nullptr) previous->dettach(this);

        move(newPos);

        Brick* b = getCloser();
        if (lastCloser != nullptr && b != lastCloser) {
            lastCloser->removeShadow();
        }
        lastCloser = nullptr;
        if (b != nullptr) {
            if (!b->isShadow()) {
                b->makeShadow(pos());
                lastCloser = b;
            }
        }

        if (owner != nullptr) {
            ((StatementBrick*)owner)->removeBrick(this);
            setOwner(nullptr);
        }
    }
}

bool Brick::isShadow() {
    return _isShadow;
}

void Brick::removeShadow() {
    if (shadow != nullptr) {
        Brick* next = shadow->next;
        dettach(shadow);
        delete shadow;
        shadow = nullptr;
        attach(next);
    }
}

void Brick::makeShadow(QPoint pos) {
    if (shadow != nullptr) return;
    shadow = new Shadow(parentWidget());
    attach(shadow);
}

void Brick::setPrevious(Brick* brick) { previous = brick; }

void Brick::setNext(Brick* brick) { this->next = brick; }

Brick* Brick::tail() {
    if (next == nullptr) return this;
    return next->tail();
}

void Brick::attach(Brick* brick) {
    if (brick == nullptr) return;

    if (next != nullptr) {
        Brick* _tail = brick->tail();
        _tail->setNext(next);
        next->setPrevious(_tail);
    }

    this->setNext(brick);
    brick->setPrevious(this);

    brick->setOwner(owner);
    brick->setZOrder(z_order);

    QPoint p = this->pos();
    p.setY(p.y() + this->height());
    brick->move(p);
    
    if (owner != nullptr) owner->recalculateSize();
}

void Brick::dettach(Brick* brick) {
    if (next != brick || brick == nullptr) return;

    this->setNext(nullptr);
    brick->setOwner(nullptr);

    QPoint p = this->pos();
    p.setY(p.y() + this->height());
    brick->move(p);

    if (owner != nullptr) owner->recalculateSize();
}

void Brick::setOwner(StatementBrick* owner) {
    this->owner = owner;
    if (next != nullptr) next->setOwner(owner);
}

void Brick::recalculateSize() {
    int h = height();
    int newW = getWidth();
    int newH = getHeight() + PIN_H;

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);

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

void Brick::setZOrder(int z) {
    if (Board* b = dynamic_cast<Board*>(parentWidget())) {
        ((Board*)parentWidget())->setZOrder(this, z_order, z);
        z_order = z;
        if (next != nullptr) next->setZOrder(z);
    }
    else {
        this->raise();
    }
}

Brick* Brick::getCloser() {
    QPoint point;
    point.setY(pos().y() - 15);
    point.setX(pos().x() + 2 * EDGE_RADIUS + PIN_H);
    QWidget* widget = parentWidget()->childAt(point);
    if (Brick* b = dynamic_cast<Brick*>(widget)) return b;
    return nullptr;
}

Brick::~Brick() {
    ((Board*)parentWidget())->removeOrder(this, z_order);
}

QPen Brick::getContourPen() { return contourPen; }

QList<Parameter> Brick::getParams() { return params; }

QString Brick::getName() { return functionName; }

QWidget* Brick::getWidget() { return (QWidget*) this; }