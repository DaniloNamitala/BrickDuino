#include "Parameter.h"
#include "Util.h"
#include "TypeMatchException.h"
#include "ValueBrick.h"

Parameter::Parameter(ValueType type) {
    this->type = type;
    this->value = nullptr;
}

Parameter::Parameter() : Parameter(ValueType::ANY) { }

ValueType Parameter::getType() {
    return type;
}
 
QSize Parameter::size(QFont font) {
    if (value != nullptr) return value->size();
    return QSize(EMPTY_VALUE_WIDTH, EMPTY_VALUE_HEIGHT);
}

void Parameter::reposition(QPoint pos) {
    if (value != nullptr) {
        value->move(pos + origin);
    }
}

Workspace::ValueBrick* Parameter::getValue() {
    return this->value; 
}

void Parameter::paint(QPainter* painter, QPoint origin, QPoint parentPos) {
    painter->save();
    painter->translate(origin);
    this->origin = origin;
    QPainterPath path2;
    int x = 0;

    if (value == nullptr) {
        path2.moveTo(x + (EMPTY_VALUE_HEIGHT / 2) , 0);
        path2.arcTo(x, 0, EMPTY_VALUE_HEIGHT, EMPTY_VALUE_HEIGHT, 90, 180);
        path2.lineTo(x + EMPTY_VALUE_WIDTH - (EMPTY_VALUE_HEIGHT / 2), 0 + EMPTY_VALUE_HEIGHT);
        path2.arcTo(x + EMPTY_VALUE_WIDTH - EMPTY_VALUE_HEIGHT, 0, EMPTY_VALUE_HEIGHT, EMPTY_VALUE_HEIGHT, 270, 180);
        path2.lineTo(x + (EMPTY_VALUE_HEIGHT / 2), 0);

        painter->setBrush(painter->brush().color().darker(150));
        painter->drawPath(path2);
    } else {
        value->move(parentPos + origin);
    }
    
    painter->translate(-origin);
    painter->restore();
}

void Parameter::setValue(Workspace::ValueBrick* value) {
    this->value = value;
}