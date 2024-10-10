#include "Value.h"

#include <QException>
#include "TypeMatchException.h"
#include "Util.h"

#define TRUE "VERDADEIRO"
#define FALSE "FALSO"

Value::Value(ValueType type, QColor color) {
    this->color = color;
    this->type = type;
    this->value = NULL;
}

Value::Value() {
    this->type = ValueType::UNDEFINED;
    this->color = VALUE_COLOR;
    this->value = NULL;
}

Value::Value(const char* value) : Value(ValueType::STRING, VALUE_COLOR) { 
    this->value = (void*) new QString(value);
};

Value::Value(int value) : Value(ValueType::INT, VALUE_COLOR) { 
    this->value = (void*) new int(value);
};

Value::Value(float value) : Value(ValueType::FLOAT, VALUE_COLOR) { 
    this->value = (void*) new float(value);
};

Value::Value(bool value) : Value(ValueType::BOOL, VALUE_COLOR) { 
    this->value = (void*) new bool(value);
};

void Value::paint(QPainter* painter, QPoint origin) {
    painter->translate(origin);

    QPainterPath path;
    QSize s = size();

    path.moveTo((s.height() / 2) , 0);
    path.arcTo(0, 0, s.height(), s.height(), 90, 180);
    path.lineTo(s.width() - (s.height() / 2), s.height());
    path.arcTo(s.width() - s.height(), 0, s.height(), s.height(), 270, 180);
    path.lineTo((s.height() / 2), 0);

    painter->save();
    QPen pen = Util::contourPen(color);
    pen.setColor(color);
    painter->setPen(pen);
    painter->setBrush(color.darker(150));

    painter->drawPath(path);

    int text_x = (s.width() - Util::textSize(toString(), Util::font()).width()) / 2;
    int text_y = Util::textSize(toString(), Util::font()).height();

    painter->setPen(Util::textPen());
    painter->drawText(QPoint(text_x, text_y), toString());
    painter->restore();
    painter->translate(-origin);
};

bool Value::isEmpty() {
    return value == NULL;
}

QSize Value::size() {
    int width = Util::textSize(toString(), Util::font()).width() + 2*VALUE_MARGIN;
    width = qMax(MIN_VALUE_WIDTH, width);
    return QSize(width, MIN_VALUE_HEIGHT);
}

QString Value::toString() {
    switch (type) {
        case ValueType::FLOAT:
            return QString::number(*(float*)value);
        case ValueType::INT:
            return QString::number(*(int*)value);
        case ValueType::STRING:
            return *((QString*)value);
        case ValueType::BOOL:
            return *((bool*)value) ? TRUE : FALSE ;
        default:
            throw new TypeMatchException("Value type not defined");
    }
}

ValueType Value::getType() {
    return type;
}
