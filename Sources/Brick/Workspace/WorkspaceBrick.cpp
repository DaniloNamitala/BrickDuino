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
#include "FunctionBrick.h"
#include "LiteralValueBrick.h"

#define X(a, b) b,
const char* type_name[] = {
  TYPE_TABLE
};
#undef X

#define X(a, b) b,
const char* value_type_name[] = {
  VALUE_TYPE_TABLE
};
#undef X

Workspace::Brick::Brick(QWidget* parent, const char* message, const char* name, QColor color) : PaintableBrick(parent, message, name, color) {
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

Workspace::Brick::Brick(const char* message, const char* name, QColor color) : Brick(nullptr, message, name, color) { }

namespace Workspace {
    QDataStream & operator >> (QDataStream &in, Workspace::Brick* &c)
    {
        QString message;
        QString name;
        BrickType type;
        QColor color;
        in >> message;
        in >> name;
        in >> type;
        in >> color;

        if (type == BrickType::FUNCTION) 
            c = new Workspace::FunctionBrick(message.toStdString().c_str(), name.toStdString().c_str(), color);
        else if (type == BrickType::STATEMENT) 
            c = new Workspace::StatementBrick(message.toStdString().c_str(), name.toStdString().c_str(), color);
        else if (type == BrickType::VALUE) 
            c = new Workspace::ValueBrick(message.toStdString().c_str(), name.toStdString().c_str(), color);
        else if (type == BrickType::LITERAL_VALUE)
            c = new Workspace::LiteralValueBrick(message.toStdString().c_str(),name.toStdString().c_str(), color);
        else 
            c = nullptr;
        
        if (c != nullptr) {
            ValueType p_type;
            QString p_name;
            while (!in.atEnd()) {
                in >> p_type;
                in >> p_name;
                c->addParam(Parameter(p_type, p_name));
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

void Workspace::Brick::mousePressEvent(QMouseEvent* event) { 
    mousePos = event->pos(); 
    if (configRect().contains(event->pos())) {
        openConfig();
    }
}

void Workspace::Brick::openConfig(){
    // NOTHING TO DO
}

void Workspace::Brick::removeParam(Brick* value) {
    if (value->getType() != BrickType::VALUE) return;

    for (Parameter& p : params)
        if (p.getValue() == value) {
            p.setValue(nullptr);
            value->setOwner(nullptr);
            recalculateSize();
            return;
        }
}

void Workspace::Brick::insertParam(Brick* value) {
    if (value->getType() != BrickType::VALUE) return;

    for (Parameter& p : params)
        if (p.outlined()) {
            p.setValue((ValueBrick*) value);
            value->setZOrder(z_order + 1);
            value->setOwner(this);
            recalculateSize();
            return;
        }
}

QJsonObject Workspace::Brick::GetJson() {    
    QJsonObject json;
    json["name"] = this->name;
    json["type"] = type_name[this->getType()];
    json["message"] = this->message;
    if (isFree()) {
        json["pos"] = tr("(") + QString::number(pos().x()) + tr(",") + QString::number(pos().y()) + tr(")");
    }

    QJsonArray jsonParams;
    if (!params.isEmpty()) {
        for (Parameter& p : params) {
            QJsonObject jsonParam;
            jsonParam["name"] = p.getName();
            jsonParam["type"] = value_type_name[p.getType()];
            if (p.getValue() != nullptr) {
                jsonParam["value"] = p.getValue()->GetJson();
            }
            jsonParams.append(jsonParam);
        }
        json["args"] = jsonParams;
    }

    QJsonArray jsonStatements;
    if (!statements.isEmpty()) {
        for (Statement& s : statements) {
            if (s.head() != nullptr) { 
                QJsonObject jsonStatement;
                jsonStatement["head"] = s.head()->GetJson();
                jsonStatements.append(jsonStatement);
            }
        }
        json["statements"] = jsonStatements;
    }

    if (previous == nullptr && next != nullptr) {
        QJsonArray chain;
        Brick* _b = next;
        while (_b != nullptr) {
            chain.append(_b->GetJson());
            _b = _b->getNext();
        }
        json["chain"] = chain;
    }
 
    return json;
}

void Workspace::Brick::setParent(QWidget* parent) {
    QWidget::setParent(parent);
    this->show();

    for (int i = 0; i < params.count(); i++)
        if (params[i].getValue() != nullptr)
            params[i].getValue()->setParent(parent);

    if (this->name == "switch_statement" && statements.last().head() == nullptr) {
        StatementBrick* _case = new StatementBrick(parent, "CASO %1 %s PADRAO %s", "case_statement" ,color.darker(-500) );
        _case->addParam(Parameter(ValueType::ANY, "case_value"));
        _case->show();
        ((StatementBrick*) this)->insertBrick(_case, 0);
    }
}

void Workspace::Brick::mouseReleaseEvent(QMouseEvent* event) {
    setCursor(QCursor(Qt::OpenHandCursor));
    setZOrder(0);
    
    if (lastCloser != nullptr) {
        if (getType() == BrickType::VALUE)
            lastCloser->insertParam(this);
        lastCloser->replaceShadow(this);
    }
    lastCloser = nullptr;
}

void Workspace::Brick::replaceShadow(Workspace::Brick* brick){
    removeShadow();
    attach(brick);
}

void Workspace::Brick::moveBrick(QPoint newPos) {
    if (name == "case_statement") return;

    setZOrder(INT16_MAX);
    setCursor(QCursor(Qt::ClosedHandCursor));

    if (previous != nullptr) 
        previous->dettach(this);

    move(newPos);
    Brick* b = getCloser();
    if (lastCloser != nullptr && b != lastCloser) {
        lastCloser->removeShadow();
        lastCloser->highlightParam(pos(), false);
    }
    lastCloser = nullptr;
    if (b != nullptr) {
        if (!b->isShadow()) {
            if (getType() == BrickType::VALUE)
                b->highlightParam(pos(), true);
            else
                b->makeShadow(pos());
            lastCloser = b;
        }
    }

    if (getType() == BrickType::VALUE && owner != nullptr) {
        owner->removeParam(this);
    }

    if (getType() != BrickType::VALUE && owner != nullptr) {
        ((Workspace::StatementBrick*) owner)->removeBrick(this);
        setOwner(nullptr);
    }
}

void Workspace::Brick::mouseMoveEvent(QMouseEvent* event) {
    setCursor(QCursor(Qt::OpenHandCursor));
    if (showConfig() && configRect().contains(event->pos()))
        setCursor(QCursor(Qt::PointingHandCursor));

    if (event->buttons() & Qt::LeftButton) {
        QPoint newPos = mapToParent(event->pos()) - mousePos;
        moveBrick(newPos);
    }
}

bool Workspace::Brick::isShadow() {
    return _isShadow;
}

bool Workspace::Brick::isFree() {
    return previous == nullptr && owner == nullptr;
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

void Workspace::Brick::highlightParam(QPoint pos, bool value) {
    if (!value) {
        for (Parameter& p : params) 
            p.highlight(false);
        
        recalculateSize();
        return;
    }


    for (Parameter& p : params) {
        QPoint _pos = this->pos() + p.pos() + QPoint(-10, -10);
        QSize size = p.size() + QSize(20, 20);
        QRect rect(_pos, size);
        if (rect.contains(pos)) {
            p.highlight(value);
        } else {
            p.highlight(false);
        }
    }
    recalculateSize();
}


void Workspace::Brick::makeShadow(QPoint pos) {
    if (shadow != nullptr) return;
    this->shadow = new Shadow(parentWidget());
    attach(shadow);
}

void Workspace::Brick::setPrevious(Brick* brick) { previous = brick; }

void Workspace::Brick::setNext(Brick* brick) { this->next = brick; }

Workspace::Brick* Workspace::Brick::tail() {
    if (next == nullptr) return this;
    return next->tail();
}

void Workspace::Brick::attach(Brick* brick) {
    if (brick == nullptr || brick->getType() == BrickType::VALUE || getType() == BrickType::VALUE) return;

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

void Workspace::Brick::addParam(Parameter param) {
    PaintableBrick::addParam(param);

    if (param.getType() == ValueType::LITERAL) {
        Brick* b = new LiteralValueBrick("FUNCTION", "literal_value", QColor(0x82101b));
        b->setOwner(this);
        b->hide();
        params.last().setValue((ValueBrick*) b);
        recalculateSize();
    }
}

void Workspace::Brick::dettach(Brick* brick) {
    if (brick == nullptr && brick->getType() == BrickType::VALUE) return;
    if (brick == nullptr && brick != next) return;

    this->setNext(nullptr);
    brick->setOwner(nullptr);
    brick->setPrevious(nullptr);

    QPoint p = this->pos();
    p.setY(p.y() + this->height());
    brick->move(p);

    if (owner != nullptr) 
        owner->recalculateSize();
}

void Workspace::Brick::setOwner(Brick* owner) {
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
    update();
}

void Workspace::Brick::move(const QPoint& pos) {
    QPoint p(pos.x(), pos.y() - PIN_H);
    QWidget::move(p);
    for (int i=0; i< params.count(); i++) {
        params[i].reposition(p);
    }
    if (next != nullptr) {
        p.setY(p.y() + this->height());
        next->move(p);
    }
}

void Workspace::Brick::setZOrder(int z) {
    if (Board* b = dynamic_cast<Board*>(parentWidget())) {
        ((Board*)parentWidget())->setZOrder(this, z_order, z);
        z_order = z;
        for (int i=0; i<params.count(); i++) 
            if (params[i].getValue() != nullptr)
                params[i].getValue()->setZOrder(z+1);
        if (next != nullptr) next->setZOrder(z);
    }
    else {
        this->raise();
    }
}

Workspace::Brick* Workspace::Brick::getCloser() {
    QPoint point;
    point.setY(pos().y() - 5);
    point.setX(pos().x() + 2 * EDGE_RADIUS + PIN_H);
    QWidget* widget = parentWidget()->childAt(point);
    if (Brick* b = dynamic_cast<Brick*>(widget)) return b;
    return nullptr;
}

Workspace::Brick::~Brick() {
    ((Board*)parentWidget())->removeOrder(this, z_order);
}