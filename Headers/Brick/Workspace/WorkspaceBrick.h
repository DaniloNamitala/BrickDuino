#pragma once

#include <QtCore>
#include <QtWidgets>
#include "PaintableBrick.h"


namespace Workspace {
    class StatementBrick;
    class Shadow;
    class Brick : public PaintableBrick {
        friend class StatementBrick;

    protected:
        QBrush brush;
        QPoint origin;
        QPoint mousePos;

        Brick* owner;
        Brick* next;
        Brick* previous;
        Brick* shadow;
        Brick* lastCloser;

        bool _isShadow;
        int z_order;

        void recalculateSize() override;

        void mouseMoveEvent(QMouseEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;

        Brick* getCloser();
        virtual void openConfig();
    public:
        void mouseReleaseEvent(QMouseEvent* event) override;
        Brick(QWidget* parent, const char* name, QColor color);
        Brick(const char* name, QColor color);
        ~Brick();
        void setOwner(Brick* owner);
        void setPrevious(Brick* brick);
        void setNext(Brick* brick);
        Brick* getNext();
        void attach(Brick* brick);
        void dettach(Brick* brick);
        void setColor(QColor color);
        bool isShadow();
        Brick* tail();

        void moveBrick(QPoint newPos);

        virtual void makeShadow(QPoint pos, bool value);
        virtual void removeShadow();
        virtual void replaceShadow(Brick* brick);

        virtual void setZOrder(int z);
        virtual void move(const QPoint& pos);
        friend QDataStream & operator >> (QDataStream &in,  Brick* &c);
    };
};  // namespace Workspace
