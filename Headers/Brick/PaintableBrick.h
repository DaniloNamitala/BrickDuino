#pragma once

#include "IPaintableBrick.h"
#include "IPainter.h"
#include <QtWidgets>
#include <QtCore> 

class PaintableBrick : public IPaintableBrick, public QWidget {
protected:
    QList<Parameter> params;
    QList<Statement> statements;
    QPen pen;
    QColor color;
    QString name;

    IPainter* painter;

    void recalculateSize() override;
    int getWidth() override;
    int getHeight() override;
public:
    PaintableBrick(QWidget* parent, const char* name, QColor color);

    QList<Parameter> getParams() override;
    QPen getContourPen() override;
    QColor getColor() override;
    QString getName() override;
    QWidget* getWidget() override;
    QList<Statement> getStatements() override;
    int headerHeight() override;

    void addParam(Parameter param);
    void paintEvent(QPaintEvent* event) override;

};