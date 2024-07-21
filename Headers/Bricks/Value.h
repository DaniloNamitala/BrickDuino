#pragma once

#include <QtWidgets>
#include <QtCore>
#include "IBrick.h"

#define MIN_VALUE_HEIGHT 20
#define MIN_VALUE_WIDTH 40
#define VALUE_MARGIN 8

#define VALUE_COLOR QColor(0xFF6600)

enum ValueType {
    INT,
    DOUBLE,
    STRING,
    BOOL,
    UNDEFINED
};

class Value : public IBrick {
private:
    QColor color;
    ValueType type;
    void* value;
    
    Value(ValueType type, QColor color);
public:
    Value();
    Value(const char* value);
    Value(int value);
    Value(double value);
    Value(bool value);
    ValueType getType();
    void paint(QPainter* painter, QPoint origin) override;
    bool isEmpty();
    QString toString();
    QSize size() override;

};

