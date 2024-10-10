#include "ToolboxStatementBrick.h"
#include "StatementBrickPainter.h"

Toolbox::StatementBrick::StatementBrick(const char* name, QColor color) : Toolbox::Brick(name, color) {
    this->painter = new StatementBrickPainter();
}

int Toolbox::StatementBrick::getHeight() {
    return EMPTY_STATEMENT_GAP + headerHeight() + BRACKET_WIDTH ;
}

int Toolbox::StatementBrick::headerHeight() {
    return Toolbox::Brick::getHeight();
}