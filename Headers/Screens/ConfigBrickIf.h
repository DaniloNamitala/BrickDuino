#pragma once

#include <QtCore>
#include <QDialog>
#include "StatementBrick.h"

class ConfigBrickIf : public QDialog {
    private:
        Workspace::StatementBrick* _brick;
    public:
        ConfigBrickIf(Workspace::StatementBrick* brick, QWidget* parent);
};