#pragma once

#include <QtCore>

class IBrick {

protected:
    virtual int height() = 0;
    virtual int width() = 0;

public:
    virtual void paint(QPainter* painter, QPoint origin) = 0;
    virtual QSize size() = 0;
    virtual ~IBrick() {}
};