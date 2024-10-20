#pragma once

#include <QtCore>
#include <QtWidgets>
#include <iostream>
#include "Value.h"
#include "Value.h"


#define MARGIN 8
#define EMPTY_VALUE_WIDTH MIN_VALUE_WIDTH
#define EMPTY_VALUE_HEIGHT MIN_VALUE_HEIGHT


class Parameter {
    private:
        ValueType type;
        Value value;
    public:
        Parameter();
        Parameter(ValueType type);
        QSize size(QFont font);
        void paint(QPainter* painter, QPoint origin);
        void setValue(Value value);
        ValueType getType();
};