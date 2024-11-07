#include "ToolboxStatementBrick.h"
#include "StatementBrickPainter.h"
#include "Util.h"

Toolbox::StatementBrick::StatementBrick(const char* name, QColor color) : Toolbox::Brick(name, color) {
    this->painter = new StatementBrickPainter();
    for (int i = 0; i < QString(name).count("%s"); i++) {
        this->statements.append(Statement());
    }
    lines.clear();
    lines = QString(name).split("%s");
    lines.removeAll("");
}

BrickType Toolbox::StatementBrick::getType() {
    return BrickType::STATEMENT;
}