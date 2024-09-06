#pragma once

#include <QtCore>
#include <QtWidgets>
#include "Parameter.h"

#define MARGIN 8
#define PIN_H 5
#define EDGE_RADIUS 6
#define BRICK_MIN_HEIGHT 20
#define CONTOUR_COLOR_DARKER 300

class StatementBrick;
class Brick : public QWidget
{
    friend class StatementBrick;
    protected:
        QColor color;
        QBrush brush;
        QPen contourPen;
        QPoint origin;
        QPen drawPen;
        QString functionName;
        QList<Parameter> params;
        QPoint mousePos;

        StatementBrick* owner;
        Brick* next;
        Brick* previous;
        Brick* shadow;
        Brick* lastCloser;

        bool _isShadow;
        int z_order;

        QColor getColor();
        void recalculateSize();

        void mouseMoveEvent(QMouseEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;

        Brick* getCloser();
    public:
        Brick(QWidget* parent, const char* name, QColor color);
        ~Brick();
        void addParam(Parameter param);
        void setOwner(StatementBrick* owner);
        void setPrevious(Brick* brick);
        void setNext(Brick* brick);
        void attach(Brick* brick);
        void dettach(Brick* brick);
        void setColor(QColor color);
        bool isShadow();
        Brick* tail();
        
        virtual void makeShadow(QPoint pos);
        virtual void removeShadow();
        virtual void replaceShadow(Brick* brick);

        virtual int getWidth();
        virtual int getHeight();
        virtual void setZOrder(int z);
        virtual void move(const QPoint &pos);
};

