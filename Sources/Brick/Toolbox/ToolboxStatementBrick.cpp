#include "ToolboxStatementBrick.h"
#include "StatementBrickPainter.h"
#include "Util.h"

Toolbox::StatementBrick::StatementBrick(const char* name, QColor color) : Toolbox::Brick(name, color) {
    this->painter = new StatementBrickPainter();
    for (int i=0; i< this->name.count("%s"); i++) {
        this->statements.append(Statement());
    }
}

int Toolbox::StatementBrick::getHeight() {
    int statementCount = name.count("%s");
    QList<QString> lines = name.split("%s");
    lines.removeAll("");
    int lineCount = lines.size();

    int height = statementCount * EMPTY_STATEMENT_GAP;

    QFontMetrics fm(Util::font());
    QRegularExpression re("(%[0-9]+)");
    for (QString line : lines) {
        int lineHeight = 2*MARGIN;
        QRegularExpressionMatchIterator i = re.globalMatch(line);
        if (i.hasNext() && params.count()) {
            height += qMax(fm.height(), params[0].size(Util::font()).height());
        } else {
            height += fm.height();
        }
        height += lineHeight;
    }
    if (lines.size() == statementCount) {
        height += BRACKET_WIDTH;
    }
    return height;
}

int Toolbox::StatementBrick::headerHeight() {
    return Toolbox::Brick::getHeight();
}

Toolbox::BrickType Toolbox::StatementBrick::getType() {
    return Toolbox::BrickType::STATEMENT;
}