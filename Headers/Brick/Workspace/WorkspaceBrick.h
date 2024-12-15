#pragma once

#include <QtCore>
#include <QtWidgets>
#include "PaintableBrick.h"


namespace Workspace {
    class StatementBrick;
    class VakueBrick;
    class Shadow;
    class Brick : public PaintableBrick {
        friend class StatementBrick;
        friend class ValueBrick;

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
        Brick(QWidget* parent, const char* message, const char* name, QColor color);
        Brick(const char* message, const char* name, QColor color);
        ~Brick();
        void setOwner(Brick* owner);
        void setPrevious(Brick* brick);
        void setNext(Brick* brick);
        Brick* getNext();
        void attach(Brick* brick);
        void dettach(Brick* brick);
        void setColor(QColor color);
        bool isShadow();
        bool isFree();
        Brick* tail();

        void moveBrick(QPoint newPos);

        virtual void makeShadow(QPoint pos);
        virtual void highlightParam(QPoint pos, bool value);
        virtual void removeShadow();
        virtual void replaceShadow(Brick* brick);
        virtual void insertParam(Brick* value);
        virtual void removeParam(Brick* value);
        void setParent(QWidget* parent);
        void addParam(Parameter param) override;

        QJsonObject GetJson();

        virtual void setZOrder(int z);
        virtual void move(const QPoint& pos);
        friend QDataStream & operator >> (QDataStream &in,  Brick* &c);
    };
};  // namespace Workspace
