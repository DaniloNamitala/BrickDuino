#pragma once

#include <QtCore>
#include <QtWidgets>
#include <iostream>
#include "Value.h"


#define MARGIN 8
#define EMPTY_VALUE_WIDTH MIN_VALUE_WIDTH
#define EMPTY_VALUE_HEIGHT MIN_VALUE_HEIGHT

namespace Workspace {
    class ValueBrick;
};

class Parameter {
    private:
        ValueType type;
        Workspace::ValueBrick* value;
        QPoint origin;
    public:
        Parameter();
        Parameter(ValueType type);
        QSize size(QFont font);
        void paint(QPainter* painter, QPoint origin, QPoint parentPos);
        void setValue(Workspace::ValueBrick* value);
        void reposition(QPoint pos);
        ValueType getType();
        Workspace::ValueBrick* getValue();
};