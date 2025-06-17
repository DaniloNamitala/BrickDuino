#pragma once

#include <QtCore>
#include <QtWidgets>
#include <QSvgWidget>
#include "WorkspaceBrick.h"


#define BOARD_BACKGROUND_COLOR QColor(0x1B1B1B)

class Board : public QWidget
{   
    private:
        QColor background;
        QPainter painter;
        QMap<int, QList<QWidget*>> zOrder;

        QList<Workspace::Brick*> bricks;
        Workspace::Brick* previewBrick;
        QMap<QString, ValueType> variables;
        QSvgWidget* trashCan;
        bool trashOpen = false;

        void createMainFunction();

    protected:
        void paintEvent(QPaintEvent* event) override;

        void dragMoveEvent(QDragMoveEvent* event) override;
        void dragEnterEvent(QDragEnterEvent* event) override;
        void dropEvent(QDropEvent* event) override;
        void dragLeaveEvent(QDragLeaveEvent* event) override;

    public:
        Board(QColor bgColor);
        ~Board();
        void setZOrder(QWidget* widget, int old_z, int new_z);
        void deleteBrick(QWidget* widget, int zOrder);
        void removeOrder(QWidget* widget, int z_order);
        QJsonDocument saveToFile(QString path);
        void addVariable(QString name, ValueType type);
        bool variableExist(QString name);
        void loadTrash(bool open);
};

