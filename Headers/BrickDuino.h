#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>

class BrickDuino : public QMainWindow
{
public:
    explicit BrickDuino(QWidget *parent = nullptr);
    ~BrickDuino();
};