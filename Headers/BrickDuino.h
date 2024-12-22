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

    // for saving
    QString _path;
    QMenu* fileMenu;
    QAction* saveAct;
    QAction* saveAsAct;

    // for compiling
    QJsonDocument _document;
    QString _compilePath;
    QMenu* compileMenu;
    QAction* compileAct;

    void createBlockToolbox();
    void loadBlocksFromJson(const char* path, QLayout* layout);
    void createBlockBoard();
    void createActions();
    void createMenus();
    void saveFile();
    void saveFileAs();
    void compileProject();
public:
    explicit BrickDuino(QWidget *parent = nullptr);
    ~BrickDuino();
};