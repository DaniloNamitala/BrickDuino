#pragma once

#include <QtWidgets>
#include <QtCore>

#define MIN_VALUE_HEIGHT 20
#define MIN_VALUE_WIDTH 40
#define VALUE_MARGIN 8

#define VALUE_COLOR QColor(0xFF6600)

enum ValueType {
    INT,
    FLOAT,
    STRING,
    BOOL,
    UNDEFINED
};

class Value {
private:
    QColor color;
    ValueType type;
    void* value;
    
    Value(ValueType type, QColor color);
public:
    Value();
    Value(const char* value);
    Value(int value);
    Value(float value);
    Value(bool value);
    ValueType getType();
    void paint(QPainter* painter, QPoint origin);
    bool isEmpty();
    QSize size();
    QString toString();

    
};

