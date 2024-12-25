#include "LiteralValueBrick.h"
#include "ValueBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Util.h"


Workspace::LiteralValueBrick::LiteralValueBrick(QWidget* parent, const char* message, const char* name, QColor color) : Workspace::ValueBrick(parent, message, name, color) {
    lineEdtMessage = new LineEdit(this);
    lineEdtMessage->resize(QSize(MIN_VALUE_WIDTH, MIN_VALUE_HEIGHT));
    lineEdtMessage->setMinimumSize(MIN_VALUE_WIDTH, MIN_VALUE_HEIGHT);
    lineEdtMessage->setFont(Util::font());
    lineEdtMessage->hide();
    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Base, color.darker(200));
    lineEdtMessage->setPalette(*palette);
    recalculateSize();
    

    connect(lineEdtMessage, &QLineEdit::textChanged, this, &LiteralValueBrick::lineEditChanged);
    connect(lineEdtMessage, &QLineEdit::editingFinished, this, &LiteralValueBrick::lineEditDone);
    connect(lineEdtMessage, &QLineEdit::inputRejected, this, &LiteralValueBrick::lineEditReject);
}
Workspace::LiteralValueBrick::LiteralValueBrick(const char* message, const char* name, QColor color) : LiteralValueBrick(nullptr, message, name, color) { }

int Workspace::LiteralValueBrick::getHeight() {
    if (lineEdtMessage->isHidden()) ValueBrick::getHeight();

    QFontMetrics fm(Util::font_sm());
    int h = qMax(MIN_VALUE_HEIGHT, fm.height());

    if (!lineEdtMessage->isHidden())
        h = qMax(h, lineEdtMessage->height());

    h += (2 * VALUE_BRICK_MARGIN);
    return h;
}

int Workspace::LiteralValueBrick::getWidth() {
    if (lineEdtMessage->isHidden()) ValueBrick::getWidth();

    int w = qMax(headerSize(0).width(), MIN_VALUE_WIDTH + 2 * MARGIN);
    if (!lineEdtMessage->isHidden())
        w = qMax(w, lineEdtMessage->width()+2*MARGIN);
    return w;
}

void Workspace::LiteralValueBrick::lineEditReject() {
    lineEdtMessage->hide();
    lineEdtMessage->clearFocus();
    recalculateSize();
}

void Workspace::LiteralValueBrick::lineEditDone() {
    message = lineEdtMessage->text();
    lines[0] = message;
    lineEdtMessage->hide();
    lineEdtMessage->clearFocus();
    recalculateSize();
}

void Workspace::LiteralValueBrick::mouseDoubleClickEvent(QMouseEvent* event) { 
    lines[0] = "";
    lineEdtMessage->show();
    lineEdtMessage->setText(message);
    lineEdtMessage->setFocus();
    message = "";
    lineEdtMessage->move(QPoint(MARGIN, VALUE_BRICK_MARGIN));
    recalculateSize();
}


void Workspace::LiteralValueBrick::lineEditChanged(const QString &text) {
    QFontMetrics fm(lineEdtMessage->font());
    int w = fm.horizontalAdvance(text) + 20;
    lineEdtMessage->resize(QSize(w, MIN_VALUE_HEIGHT));
    recalculateSize();
}

BrickType Workspace::LiteralValueBrick::getType() {
    return BrickType::VALUE;
}