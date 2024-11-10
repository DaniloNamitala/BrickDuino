#pragma once
#include <QtWidgets>
#include <QtCore>
#include "Parameter.h"
#include "Statement.h"

enum BrickType {
    FUNCTION,
    STATEMENT,
    VALUE,
    UNDEFINED
};

class IPaintableBrick {
   public:
    virtual QList<Parameter>& getParams() = 0;
    virtual QPen getContourPen() = 0;
    virtual QColor getColor() = 0;
    virtual QString getMessage() = 0;
    virtual QWidget* getWidget() = 0;
    virtual QList<Statement> getStatements() = 0;
    virtual QList<QString> getLines() = 0;
    
    virtual void recalculateSize() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual QSize headerSize(int index) = 0;
    virtual bool showConfig() = 0;
    virtual QRect configRect() = 0;
    virtual QPixmap** getCache() = 0;
    virtual BrickType getType() = 0;
};