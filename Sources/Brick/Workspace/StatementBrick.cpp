#include "StatementBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Shadow.h"
#include "Util.h"
#include "StatementBrickPainter.h"

Workspace::StatementBrick::StatementBrick(QWidget* parent, const char* name, QColor color) : Workspace::Brick(parent, name, color) {
    this->statementHead = nullptr;
    painter = new StatementBrickPainter();
    recalculateSize();
 }

Workspace::StatementBrick::StatementBrick(const char* name, QColor color) : Workspace::StatementBrick(nullptr, name, color) { }

int Workspace::StatementBrick::headerHeight() {
    return Workspace::Brick::getHeight();
}

int Workspace::StatementBrick::statementHeight() {
    if (statementHead == nullptr) return EMPTY_STATEMENT_GAP;

    int height = 0;
    Workspace::Brick* actual = statementHead;
    do {
        height += actual->getHeight();
        actual = actual->next;
    } while (actual != nullptr);

    return height;
}

int Workspace::StatementBrick::getHeight() {
    int instructionsHeight = statementHeight();
    return instructionsHeight + headerHeight() + BRACKET_WIDTH ;
}

QPoint Workspace::StatementBrick::getStatementOrigin() {
    return QPoint(BRACKET_WIDTH, headerHeight());
}

void Workspace::StatementBrick::removeBrick(Workspace::Brick* brick) {
    if (brick == statementHead)
        this->statementHead = nullptr; 
    recalculateSize();
}

void Workspace::StatementBrick::insertBrick(Brick* brick) {
    this->statementHead = brick;
    this->stackUnder(brick);
    QPoint p(pos().x() + BRACKET_WIDTH, pos().y() + headerHeight() + PIN_H);
    
    brick->setOwner(this);
    brick->setZOrder(z_order + 1);
    brick->move(p);
    recalculateSize();
}

void Workspace::StatementBrick::move(const QPoint &pos) {
    Workspace::Brick::move(pos);

    QPoint p(pos.x() + BRACKET_WIDTH, pos.y() + headerHeight());
    if (statementHead != nullptr) 
        statementHead->move(p);
}

void Workspace::StatementBrick::setZOrder(int z) {
    Workspace::Brick::setZOrder(z);
    if (statementHead != nullptr)
        statementHead->setZOrder(z+1);
}

void Workspace::StatementBrick::removeShadow() {
    if (shadow != nullptr) {

        if (next == shadow) {
            Workspace::Brick* next = shadow->next;
            dettach(shadow);
            delete shadow;
            shadow = nullptr;
            attach(next);
            return;
        }

        Workspace::Brick* _next = shadow->next;
        if (_next != nullptr)
            insertBrick(_next);
        else
            removeBrick(shadow);

        delete shadow;
        shadow = nullptr;
    }
}

void Workspace::StatementBrick::makeShadow(QPoint pos) {
    if (shadow != nullptr) return;
    shadow = new Shadow(parentWidget());

    QPoint _pos = this->pos();
    QPoint _posBottom = this->pos();
    _posBottom.setY(_posBottom.y() + getHeight());

    if (abs(pos.y() - _pos.y()) < abs(pos.y() - _posBottom.y())) {
        Workspace::Brick* _oldHead = statementHead;
        insertBrick(shadow);
        shadow->attach(_oldHead);
        return;
    }
    attach(shadow);
}

void Workspace::StatementBrick::replaceShadow(Brick* brick) {
    if (statementHead == shadow) {
        Workspace::Brick* _oldHead = statementHead->next;
        removeShadow();
        insertBrick(brick);

        brick->tail()->attach(_oldHead);
        return;
    }

    Workspace::Brick::replaceShadow(brick);
}