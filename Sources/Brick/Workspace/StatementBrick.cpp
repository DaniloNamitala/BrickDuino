#include "StatementBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Shadow.h"
#include "Util.h"
#include "StatementBrickPainter.h"

Workspace::StatementBrick::StatementBrick(QWidget* parent, const char* name, QColor color) : Workspace::Brick(parent, name, color) {
    painter = new StatementBrickPainter();
    for (int i = 0; i < QString(name).count("%s"); i++) {
        this->statements.append(Statement());
    }
    shadow_statement_idx = -1;
    lines.clear();
    lines = QString(name).split("%s");
    lines.removeAll("");
    recalculateSize();
 }

Workspace::StatementBrick::StatementBrick(const char* name, QColor color) : Workspace::StatementBrick(nullptr, name, color) { }

void Workspace::StatementBrick::removeBrick(Workspace::Brick* brick) {
    for (int i = 0; i < statements.count(); i++) {
        if (statements[i].head() == brick) {
            statements[i].remove(brick);
            break;
        }
    }
    recalculateSize();
}

void Workspace::StatementBrick::insertBrick(Brick* brick, int st_idx) {
    statements[st_idx].insert(brick);
    this->stackUnder(brick);
    int y = pos().y() + PIN_H;
    for (int i=0; i<st_idx; i++) {
        y += headerSize(i).height() + statements[i].height();
    }

    QPoint p(pos().x() + BRACKET_WIDTH, y + headerSize(st_idx).height());
    
    brick->setOwner(this);
    brick->setZOrder(z_order + 1);
    brick->move(p);
    recalculateSize();
}

void Workspace::StatementBrick::recalculateSize() {
    Workspace::Brick::recalculateSize();

    int y = this->pos().y() + PIN_H;
    for (int i=0; i<statements.count(); i++) {
        QPoint p(this->pos().x() + BRACKET_WIDTH, y + headerSize(i).height());
        if (statements[i].head() != nullptr) 
            statements[i].head()->move(p);
        y += headerSize(i).height() + statements[i].height();
    }
}

void Workspace::StatementBrick::move(const QPoint &pos) {
    Workspace::Brick::move(pos);

    int y = pos.y();
    for (int i=0; i<statements.count(); i++) {
        QPoint p(pos.x() + BRACKET_WIDTH, y + headerSize(i).height());
        if (statements[i].head() != nullptr) 
            statements[i].head()->move(p);
        y += headerSize(i).height() + statements[i].height();
    }
}

void Workspace::StatementBrick::setZOrder(int z) {
    Workspace::Brick::setZOrder(z);
    if (statements[0].head() != nullptr)
        statements[0].head()->setZOrder(z+1);
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
            insertBrick(_next, shadow_statement_idx);
        else
            removeBrick(shadow);
        shadow_statement_idx = -1;
        delete shadow;
        shadow = nullptr;
    }
}

void Workspace::StatementBrick::makeShadow(QPoint pos) {
    QPoint _pos = this->pos();
    QPoint _posBottom = this->pos();
    _posBottom.setY(_posBottom.y() + getHeight());

    int idxLine = 0;
    int y = this->pos().y() + PIN_H;
    int _y = y + headerSize(idxLine).height();
    while (!(y < pos.y() && pos.y() < _y) && idxLine < getLines().count()) {
        y = _y + statements[idxLine].height();
        _y = y + headerSize(idxLine).height();
        idxLine++;
    }

    if (idxLine < statements.count()) {
        if (shadow != nullptr && shadow == statements[idxLine].head()) return;
        if (shadow == nullptr)
            shadow = new Shadow(parentWidget());
        else
            dettach(shadow);
        
        shadow_statement_idx = idxLine;
        Workspace::Brick* _oldHead = statements[idxLine].head();
        insertBrick(shadow, shadow_statement_idx);
        shadow->attach(_oldHead);
        return;
    }

    if (shadow != nullptr && shadow == next) return;
    if (shadow == nullptr)
        shadow = new Shadow(parentWidget());
    else
        removeBrick(shadow);
    shadow_statement_idx = -1;
    
    attach(shadow);
}

void Workspace::StatementBrick::replaceShadow(Brick* brick) {
    if (shadow_statement_idx != -1 && statements[shadow_statement_idx].head() == shadow) {
        Workspace::Brick* _oldHead = statements[shadow_statement_idx].head()->next;
        int st_idx = shadow_statement_idx;
        removeShadow();
        insertBrick(brick, st_idx);

        brick->tail()->attach(_oldHead);
        return;
    }

    Workspace::Brick::replaceShadow(brick);
}