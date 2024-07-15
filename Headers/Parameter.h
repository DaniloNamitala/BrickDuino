#pragma once

#include <QtCore>
#include <QtWidgets>

#define MARGIN 8
#define EMPTY_VALUE_WIDTH 40
#define EMPTY_VALUE_HEIGHT 20

enum ParamType {
    INT,
    FLOAT,
    STRING,
    BOOL
};

class Parameter {
    private:
        QString textBefore;
        QString textAfter;
        ParamType type;
    public:
        Parameter(QString textBefore, QString textAfter, ParamType type);
        QSize size(QFont font);
        void paint(QPainter* painter, QPoint origin);
};