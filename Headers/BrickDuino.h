#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
#include "Board.h"

class BrickDuino : public QMainWindow
{
private:
    QDockWidget *blockToolbox;
    Board* blockBoard;

    void crteateBlockToolbox();
    void crteateBlockBoard();
public:
    explicit BrickDuino(QWidget *parent = nullptr);
    ~BrickDuino();
};