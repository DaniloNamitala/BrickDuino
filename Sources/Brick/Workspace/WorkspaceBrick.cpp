#include "WorkspaceBrick.h"

#include <QCursor>
#include <QPainter>
#include <QPainterPath>

#include "Board.h"
#include "Shadow.h"
#include "Util.h"
#include "StatementBrick.h"
#include "ValueBrick.h"
#include "ToolboxBrick.h"

Workspace::Brick::Brick(QWidget* parent, const char* name, QColor color) : PaintableBrick(parent, name, color) {
    this->z_order = -1;
    this->owner = nullptr;
    this->next = nullptr;
    this->previous = nullptr;
    this->shadow = nullptr;
    this->lastCloser = nullptr;
    this->_isShadow = false;

    setMouseTracking(true);
    recalculateSize();
    if (parent != nullptr)
        show();
}

Workspace::Brick::Brick(const char* name, QColor color) : Brick(nullptr, name, color) { }

namespace Workspace {
    QDataStream & operator >> (QDataStream &in, Workspace::Brick* &c)
    {
        QString name;
        Toolbox::BrickType type;
        QColor color;
        in >> name;
        in >> type;
        in >> color;

        if (type == Toolbox::BrickType::FUNCTION) 
            c = new Workspace::FunctionBrick(name.toStdString().c_str(), color);
        else if (type == Toolbox::BrickType::STATEMENT) 
            c = new Workspace::StatementBrick(name.toStdString().c_str(), color);
        else if (type == Toolbox::BrickType::VALUE) 
            c = new Workspace::ValueBrick(name.toStdString().c_str(), color);
        else 
            c = nullptr;
        
        if (c != nullptr) {
            ValueType p_type;
            while (!in.atEnd()) {
                in >> p_type;
                c->addParam(Parameter(p_type));
            }
        }
        return in;
    }
}

void Workspace::Brick::setColor(QColor color) {
    this->color = color;
    update();
}

Workspace::Brick* Workspace::Brick::getNext() { return next; }

void Workspace::Brick::mousePressEvent(QMouseEvent* event) { mousePos = event->pos(); }

void Workspace::Brick::mouseReleaseEvent(QMouseEvent* event) {
    setCursor(QCursor(Qt::OpenHandCursor));
    if (lastCloser != nullptr) {
        lastCloser->replaceShadow(this);
    }
    lastCloser = nullptr;
    setZOrder(0);
}

void Workspace::Brick::replaceShadow(Workspace::Brick* brick){
    removeShadow();
    attach(brick);
}

void Workspace::Brick::moveBrick(QPoint newPos) {
    setZOrder(INT32_MAX);
    setCursor(QCursor(Qt::ClosedHandCursor));

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
        ((Workspace::StatementBrick*)owner)->removeBrick(this);
        setOwner(nullptr);
    }
}

void Workspace::Brick::mouseMoveEvent(QMouseEvent* event) {
    setCursor(QCursor(Qt::OpenHandCursor));

    if (event->buttons() & Qt::LeftButton) {
        QPoint newPos = mapToParent(event->pos()) - mousePos;
        moveBrick(newPos);
    }
}

bool Workspace::Brick::isShadow() {
    return _isShadow;
}

void Workspace::Brick::removeShadow() {
    if (shadow != nullptr) {
        Workspace::Brick* next = shadow->next;
        dettach(shadow);
        delete shadow;
        shadow = nullptr;
        attach(next);
    }
}

void Workspace::Brick::makeShadow(QPoint pos) {
    if (shadow != nullptr) return;
    shadow = new Shadow(parentWidget());
    attach(shadow);
}

void Workspace::Brick::setPrevious(Brick* brick) { previous = brick; }

void Workspace::Brick::setNext(Brick* brick) { this->next = brick; }

Workspace::Brick* Workspace::Brick::tail() {
    if (next == nullptr) return this;
    return next->tail();
}

void Workspace::Brick::attach(Brick* brick) {
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

void Workspace::Brick::dettach(Brick* brick) {
    if (next != brick || brick == nullptr) return;

    this->setNext(nullptr);
    brick->setOwner(nullptr);

    QPoint p = this->pos();
    p.setY(p.y() + this->height());
    brick->move(p);

    if (owner != nullptr) owner->recalculateSize();
}

void Workspace::Brick::setOwner(StatementBrick* owner) {
    this->owner = owner;
    if (next != nullptr) next->setOwner(owner);
}

void Workspace::Brick::recalculateSize() {
    int h = height();
    PaintableBrick::recalculateSize();

    if (owner != nullptr) {
        owner->recalculateSize();
    }

    if (h != height() && next != nullptr) {
        QPoint p = this->pos();
        p.setY(p.y() + this->height());
        next->move(p);
    }
}

void Workspace::Brick::move(const QPoint& pos) {
    QPoint p(pos.x(), pos.y() - PIN_H);
    QWidget::move(p);

    if (next != nullptr) {
        p.setY(p.y() + this->height());
        next->move(p);
    }
}

void Workspace::Brick::setZOrder(int z) {
    if (Board* b = dynamic_cast<Board*>(parentWidget())) {
        ((Board*)parentWidget())->setZOrder(this, z_order, z);
        z_order = z;
        if (next != nullptr) next->setZOrder(z);
    }
    else {
        this->raise();
    }
}

Workspace::Brick* Workspace::Brick::getCloser() {
    QPoint point;
    point.setY(pos().y() - 15);
    point.setX(pos().x() + 2 * EDGE_RADIUS + PIN_H);
    QWidget* widget = parentWidget()->childAt(point);
    if (Brick* b = dynamic_cast<Brick*>(widget)) return b;
    return nullptr;
}

Workspace::Brick::~Brick() {
    ((Board*)parentWidget())->removeOrder(this, z_order);
}