#pragma once

#include <QtCore>
#include <QtWidgets>
#include "IPaintableBrick.h"
#include "IPainter.h"

#define MARGIN 8
#define PIN_H 5
#define EDGE_RADIUS 6
#define BRICK_MIN_HEIGHT 20
#define CONTOUR_COLOR_DARKER 300

class ToolboxBrick : public QWidget, public IPaintableBrick {
    private:
        QList<Parameter> params;
        QPen contourPen;
        QColor color;
        QString name;

        IPainter* painter;

        void recalculateSize();
        virtual int getWidth();
        virtual int getHeight();

    public:
        ToolboxBrick(const char* name, QColor color);

        QList<Parameter> getParams();
        QPen getContourPen();
        QColor getColor();
        QString getName();
        QWidget* getWidget();

        void addParam(Parameter param);
        void paintEvent(QPaintEvent* event) override;
};