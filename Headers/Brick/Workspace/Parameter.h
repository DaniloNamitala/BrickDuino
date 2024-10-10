#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Value.h"
#include "Value.h"

#define MARGIN 8
#define EMPTY_VALUE_WIDTH MIN_VALUE_WIDTH
#define EMPTY_VALUE_HEIGHT MIN_VALUE_HEIGHT


class Parameter {
    private:
        QString textBefore;
        QString textAfter;
        ValueType type;
        Value value;
        
    public:
        Parameter(ValueType type);
        Parameter(QString textBefore, ValueType type);
        Parameter(QString textBefore, QString textAfter, ValueType type);
        QSize size(QFont font);
        void paint(QPainter* painter, QPoint origin);
        void setValue(Value value);
};