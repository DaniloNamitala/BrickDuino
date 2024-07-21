#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"
#include "IBrick.h"

#define MARGIN 8
#define PIN_H 5
#define EDGE_RADIUS 6
#define BRICK_MIN_HEIGHT 20

class Brick : public IBrick {
    protected:
        QColor color;
        QPoint origin;
        QString name;
        QList<Parameter*> params;

        QColor getColor();
        int height() override;
        int width() override;
    public:
        Brick(const char* name, QColor color);
        void addParam(Parameter* param);
        void paint(QPainter* painter, QPoint origin) override;
        QSize size() override;
};

