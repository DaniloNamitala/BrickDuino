#include "ToolboxStatementBrick.h"
#include "StatementBrickPainter.h"
#include "Util.h"

Toolbox::StatementBrick::StatementBrick(const char* message, const char* name, QColor color) : Toolbox::Brick(message, name, color) {
    this->painter = new StatementBrickPainter();
    for (int i = 0; i < QString(message).count("%s"); i++) {
        this->statements.append(Statement());
    }
    lines.clear();
    lines = QString(message).split("%s");
    lines.removeAll("");
}

BrickType Toolbox::StatementBrick::getType() {
    return BrickType::STATEMENT;
}