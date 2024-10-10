#pragma once

#include <QtCore>
#include <QtWidgets>

#include "PaintableBrick.h"
#include "Parameter.h"

namespace Workspace {
class StatementBrick;
class Brick : public PaintableBrick {
    friend class StatementBrick;

   protected:
    QBrush brush;
    QPoint origin;
    QPoint mousePos;

    StatementBrick* owner;
    Brick* next;
    Brick* previous;
    Brick* shadow;
    Brick* lastCloser;

    bool _isShadow;
    int z_order;

    void recalculateSize() override;

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    Brick* getCloser();

   public:
    Brick(QWidget* parent, const char* name, QColor color);
    Brick(const char* name, QColor color);
    ~Brick();
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

    virtual void setZOrder(int z);
    virtual void move(const QPoint& pos);

};

};  // namespace Workspace
