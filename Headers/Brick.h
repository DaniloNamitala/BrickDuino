#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"

#define MARGIN 8
#define PIN_H 5
#define EDGE_RADIUS 6

class Brick
{
    private:
        QColor color;
        QBrush brush;
        QPoint origin;
        QPen drawPen;
        QString functionName;
        QList<Parameter> params;

        int margin;
        bool hovered;

        QColor getColor();
        QPen getPen();
    public:
        Brick(const char* name, QColor color);
        void paint(QPainter* painter, QPoint origin);
        int width();
        int height();
        bool mouseMove(QMouseEvent* event);
        bool isOver(QPoint point);
        void addParam(Parameter param);
        static QPen getTextPen();
        static QFont getFont();

};

