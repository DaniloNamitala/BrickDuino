#include "Parameter.h"
#include "Util.h"
#include "TypeMatchException.h"
#include "ValueBrick.h"
#include "LiteralValueBrick.h"

Parameter::Parameter(ValueType type) {
    this->type = type;
    this->value = nullptr;
    this->outline = false;
}

Parameter::Parameter() : Parameter(ValueType::ANY) { }

ValueType Parameter::getType() {
    return type;
}
 
QSize Parameter::size() {
    if (value != nullptr) return value->size();
    return QSize(EMPTY_VALUE_WIDTH, EMPTY_VALUE_HEIGHT);
}

void Parameter::reposition(QPoint pos) {
    if (value != nullptr) {
        value->move(pos + _origin);
    }
}

Workspace::ValueBrick* Parameter::getValue() {
    return this->value; 
}

bool Parameter::outlined() {
    return this->outline; 
}

QPoint Parameter::pos() {
    return _origin;
}

void Parameter::paint(QPainter* painter, QPoint origin, QPoint parentPos) {
    painter->save();
    this->_origin.setX(origin.x());
    this->_origin.setY(origin.y());
    QPainterPath path2;

    int x = 0;
    if (value != nullptr)
        value->move(parentPos + origin);

    if (outline) {
        QPen outlinePen;
        outlinePen.setWidth(3);
        outlinePen.setColor(QColor("#C0C0C0"));
        painter->setPen(outlinePen);
    }
    
    int w = this->size().width();
    int h = this->size().height();

    if (value == nullptr || outline) {
        if (value != nullptr) {
            w += 3;
            h += 3;
            origin -= QPoint(2,2);
        }
        
        painter->translate(origin);
        path2.moveTo(x + (h / 2) , 0);
        path2.arcTo(x, 0, h, h, 90, 180);
        path2.lineTo(x + w - (h / 2), 0 + h);
        path2.arcTo(x + w - h, 0, h, h, 270, 180);
        path2.lineTo(x + (h / 2), 0);
        painter->setBrush(painter->brush().color().darker(150));
        painter->drawPath(path2);
        painter->translate(-origin);
    }

    painter->restore();
}

void Parameter::highlight(bool value) {
    this->outline = value;
}

void Parameter::setValue(Workspace::ValueBrick* value) {
    outline = false;
    if (this->value != nullptr) {
        this->value->setOwner(nullptr);
        this->value->move(this->value->pos() + QPoint(20, 20));
    }
    this->value = value;
}