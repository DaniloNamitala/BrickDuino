#pragma once

#include "IPaintableBrick.h"
#include "IPainter.h"
#include <QtWidgets>
#include <QtCore> 
#include <QPixmap> 

class PaintableBrick : public IPaintableBrick, public QWidget {
protected:
    QList<Parameter> params;
    QString variable;
    QList<Statement> statements;
    QList<QString> lines;
    QPen pen;
    QColor color;
    QString message;
    QString name;

    QPixmap** cachePaint;

    IPainter* painter;
    bool _showConfig;

    void recalculateSize() override;
    int getWidth() override;
public:
    PaintableBrick(QWidget* parent, const char* message, const char* name, QColor color);

    QList<Parameter>& getParams() override;
    QPen getContourPen() override;
    QColor getColor() override;
    QString getMessage() override;
    QString getVariableName() override;
    QList<QString> getLines() override;
    QWidget* getWidget() override;
    QList<Statement> getStatements() override;
    QSize headerSize(int index = 0) override;
    int getHeight() override;

    virtual void addParam(Parameter param);
    void paintEvent(QPaintEvent* event) override;
    bool showConfig() override;
    QRect configRect() override;
    QPixmap** getCache() override;
    BrickType getType() override;
};