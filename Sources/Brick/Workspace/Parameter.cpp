#include "Parameter.h"
#include "Util.h"
#include "TypeMatchException.h"

Parameter::Parameter(ValueType type) {
    this->type = type;
}

Parameter::Parameter() : Parameter(ValueType::ANY) { }

ValueType Parameter::getType() {
    return type;
}
 
QSize Parameter::size(QFont font) {
    int width = !value.isEmpty() ? value.size().width() : EMPTY_VALUE_WIDTH;
    QFontMetrics fm(font);
    int height = !value.isEmpty() ? value.size().height() : EMPTY_VALUE_HEIGHT;
    return QSize(width, height);
}

void Parameter::paint(QPainter* painter, QPoint origin) {
    painter->save();
    painter->translate(origin);

    QPainterPath path2;
    int x = 0;

    if (value.isEmpty()) {
        path2.moveTo(x + (EMPTY_VALUE_HEIGHT / 2) , 0);
        path2.arcTo(x, 0, EMPTY_VALUE_HEIGHT, EMPTY_VALUE_HEIGHT, 90, 180);
        path2.lineTo(x + EMPTY_VALUE_WIDTH - (EMPTY_VALUE_HEIGHT / 2), 0 + EMPTY_VALUE_HEIGHT);
        path2.arcTo(x + EMPTY_VALUE_WIDTH - EMPTY_VALUE_HEIGHT, 0, EMPTY_VALUE_HEIGHT, EMPTY_VALUE_HEIGHT, 270, 180);
        path2.lineTo(x + (EMPTY_VALUE_HEIGHT / 2), 0);

        painter->setBrush(painter->brush().color().darker(150));
        painter->drawPath(path2);
    } else {
        value.paint(painter, QPoint(x, 0));
    }
    
    painter->translate(-origin);
    painter->restore();
}

void Parameter::setValue(Value value) {
    if (type != value.getType())
        throw new TypeMatchException("Value and parameter type doesn't match!");
    this->value = value;
}