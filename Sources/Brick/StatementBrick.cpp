#include "StatementBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Shadow.h"
#include "Util.h"

StatementBrick::StatementBrick(QWidget* parent, const char* name, QColor color) : Brick(parent, name, color) {
    this->statementHead = nullptr;
    recalculateSize();
 }

void StatementBrick::paintEvent(QPaintEvent* event) {
    QPainterPath path;
    QPainter painter(this);

    // Draw the pin
    path.moveTo(2 * EDGE_RADIUS, PIN_H);
    path.arcTo(2 * EDGE_RADIUS, 0, 2 * PIN_H, 2 * PIN_H, 180, -180);

    // Draw the right corners
    path.lineTo(Brick::getWidth() - 2 * EDGE_RADIUS, PIN_H);
    path.arcTo(Brick::getWidth() - 2 * EDGE_RADIUS, PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    path.lineTo(Brick::getWidth(), headerHeight() - 2 * EDGE_RADIUS + PIN_H);
    path.arcTo(Brick::getWidth() - 2 * EDGE_RADIUS, headerHeight() - 2 * EDGE_RADIUS + PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);

    // Draw the socket
    path.lineTo(BRACKET_WIDTH + 2 * EDGE_RADIUS + (PIN_H + contourPen.width()) * 2, headerHeight() + PIN_H);
    path.arcTo(BRACKET_WIDTH + 2 * EDGE_RADIUS - contourPen.width(), headerHeight() - (PIN_H + contourPen.width()) + PIN_H, 2 * (PIN_H + contourPen.width()), 2 * (PIN_H + contourPen.width()), 0, 180);

    path.lineTo(BRACKET_WIDTH + EDGE_RADIUS, headerHeight() + PIN_H);
    path.arcTo(BRACKET_WIDTH, headerHeight() + PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, 90);

    path.lineTo(BRACKET_WIDTH, height() - BRACKET_WIDTH - EDGE_RADIUS);
    path.arcTo(BRACKET_WIDTH, height() - BRACKET_WIDTH - 2*EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 180, 90);

    
    path.lineTo(Brick::getWidth() - 2 * EDGE_RADIUS, height() - BRACKET_WIDTH);
    path.arcTo(Brick::getWidth() - 2 * EDGE_RADIUS, height() - BRACKET_WIDTH, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 90, -90);
    path.lineTo(Brick::getWidth(), height() - 2 * EDGE_RADIUS);
    path.arcTo(Brick::getWidth() - 2 * EDGE_RADIUS, height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 0, -90);

    // Draw the socket
    path.lineTo(2 * EDGE_RADIUS + (PIN_H + contourPen.width()) * 2, height());
    path.arcTo(2 * EDGE_RADIUS - contourPen.width(), height() - (PIN_H + contourPen.width()), 2 * (PIN_H + contourPen.width()), 2 * (PIN_H + contourPen.width()), 0, 180);

    // Draw the bottom left corner
    path.lineTo(2 * EDGE_RADIUS - contourPen.width(), height());
    path.arcTo(0, height() - 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 270, -90);
    path.lineTo(0, 2 * EDGE_RADIUS + PIN_H);
    path.arcTo(0, PIN_H, 2 * EDGE_RADIUS, 2 * EDGE_RADIUS, 180, -90);
    path.lineTo(2 * EDGE_RADIUS, PIN_H);

    painter.setFont(Util::font());
    painter.setBrush(getColor());
    painter.setPen(contourPen);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPath(path);

    int funcNameWidth = Util::textSize(functionName, Util::font()).width();
    int x = MARGIN + funcNameWidth + MARGIN;
    
    for (int i = 0; i < params.size(); i++) {
        params[i].paint(&painter, QPoint(x, MARGIN + PIN_H));
        x += params[i].size(Util::font()).width() + MARGIN;
    }


    painter.setPen(Util::textPen());
    painter.drawText(MARGIN, MARGIN + Util::textSize(functionName, Util::font()).height() + PIN_H, functionName);    
}

int StatementBrick::headerHeight() {
    return Brick::getHeight();
}

int StatementBrick::statementHeight() {
    if (statementHead == nullptr) return EMPTY_STATEMENT_GAP;

    int height = 0;
    Brick* actual = statementHead;
    do {
        height += actual->getHeight();
        actual = actual->next;
    } while (actual != nullptr);

    return height;
}

int StatementBrick::getHeight() {
    int instructionsHeight = statementHeight();
    return instructionsHeight + headerHeight() + BRACKET_WIDTH ;
}

QPoint StatementBrick::getStatementOrigin() {
    return QPoint(BRACKET_WIDTH, headerHeight());
}

void StatementBrick::removeBrick(Brick* brick) {
    if (brick == statementHead)
        this->statementHead = nullptr; 
    recalculateSize();
}

void StatementBrick::insertBrick(Brick* brick) {
    this->statementHead = brick;
    this->stackUnder(brick);
    QPoint p(pos().x() + BRACKET_WIDTH, pos().y() + headerHeight() + PIN_H);
    
    brick->setOwner(this);
    brick->setZOrder(z_order + 1);
    brick->move(p);
    recalculateSize();
}

void StatementBrick::move(const QPoint &pos) {
    Brick::move(pos);

    QPoint p(pos.x() + BRACKET_WIDTH, pos.y() + headerHeight());
    if (statementHead != nullptr) 
        statementHead->move(p);
}

void StatementBrick::setZOrder(int z) {
    Brick::setZOrder(z);
    if (statementHead != nullptr)
        statementHead->setZOrder(z+1);
}

void StatementBrick::removeShadow() {
    if (shadow != nullptr) {

        if (next == shadow) {
            Brick* next = shadow->next;
            dettach(shadow);
            delete shadow;
            shadow = nullptr;
            attach(next);
            return;
        }

        Brick* _next = shadow->next;
        if (_next != nullptr)
            insertBrick(_next);
        else
            removeBrick(shadow);

        delete shadow;
        shadow = nullptr;
    }
}

void StatementBrick::makeShadow(QPoint pos) {
    if (shadow != nullptr) return;
    shadow = new Shadow(parentWidget());

    QPoint _pos = this->pos();
    QPoint _posBottom = this->pos();
    _posBottom.setY(_posBottom.y() + getHeight());

    if (abs(pos.y() - _pos.y()) < abs(pos.y() - _posBottom.y())) {
        Brick* _oldHead = statementHead;
        insertBrick(shadow);
        shadow->attach(_oldHead);
        return;
    }
    attach(shadow);
}

void StatementBrick::replaceShadow(Brick* brick) {
    if (statementHead == shadow) {
        Brick* _oldHead = statementHead->next;
        removeShadow();
        insertBrick(brick);

        brick->tail()->attach(_oldHead);
        return;
    }

    Brick::replaceShadow(brick);
}