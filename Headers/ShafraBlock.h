#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
#include "Board.h"
#include "Spoiler.h"

class ShafraBlock : public QMainWindow
{
private:
    QDockWidget *blockToolbox;
    QMap<QString, Spoiler*> spoilerMap;
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
    QAction* compileCpp;
    QAction* compilePas;
    QAction* compilePy;

    void createBlockToolbox();
    void loadBlocksFromJson(const char* path, QLayout* layout);
    void createBlockBoard();
    void createActions();
    void createMenus();
    void saveFile();
    void saveFileAs();
    void compileProject(QString extension, QString grammar);
    void addSpoilerActions();
    void createVariable(QString name, QString type);
    void modalCreateVariable();
public:
    explicit ShafraBlock(QWidget *parent = nullptr);
    ~ShafraBlock();
};