#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"

#define MARGIN 8
#define PIN_H 5
#define EDGE_RADIUS 6
#define BRICK_MIN_HEIGHT 20

class Brick
{
    protected:
        QColor color;
        QBrush brush;
        QPoint origin;
        QPen drawPen;
        QString functionName;
        QList<Parameter> params;

        QColor getColor();
        QPen getPen();
    public:
        Brick(const char* name, QColor color);

        virtual void paint(QPainter* painter, QPoint origin); 
        virtual int width();
        virtual int height();

        void addParam(Parameter param);
        static QPen getTextPen();
        static QFont getFont();

};

