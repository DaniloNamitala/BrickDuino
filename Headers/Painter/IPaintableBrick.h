#pragma once
#include <QtWidgets>
#include <QtCore>
#include "Parameter.h"

class IPaintableBrick {
   public:
    virtual QList<Parameter> getParams() = 0;
    virtual QPen getContourPen() = 0;
    virtual QColor getColor() = 0;
    virtual QString getName() = 0;
    virtual QWidget* getWidget() = 0;
    
    virtual void recalculateSize() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
};