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

    //json
    QString _fileName;
    QString _fileBuffer;
    QFile _file;
    QJsonDocument _document;
    QVariantMap _documentMap;

    QMenu* fileMenu;
    QAction* saveAct;
    QAction* saveAsAct;

    void createBlockToolbox();
    void loadBlocksFromJson(const char* path, QLayout* layout);
    void createBlockBoard();
    void createActions();
    void createMenus();
    void saveFile();
    void saveFileAs();
public:
    explicit BrickDuino(QWidget *parent = nullptr);
    ~BrickDuino();
};