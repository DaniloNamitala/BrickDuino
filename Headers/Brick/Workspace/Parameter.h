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
        QPoint _origin;
        bool outline;
        QString name;
    public:
        Parameter();
        Parameter(ValueType type, QString p_name);
        QSize size();
        void paint(QPainter* painter, QPoint origin, QPoint parentPos);
        void setValue(Workspace::ValueBrick* value);
        void reposition(QPoint pos);
        ValueType getType();
        QString getName();
        QPoint pos();
        Workspace::ValueBrick* getValue();
        void highlight(bool value);
        bool outlined();
};