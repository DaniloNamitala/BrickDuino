#include "PaintableBrick.h"
#include "Util.h"

PaintableBrick::PaintableBrick(QWidget* parent, const char* message, const char* name, QColor color): QWidget(parent) {
    this->color = color;
    this->pen = QPen(color.darker(CONTOUR_COLOR_DARKER));
    this->message = QString(message);
    this->name = QString(name);
    this->lines.append(QString(message));
    pen.setWidth(2);
    _showConfig = false;
    cachePaint = new QPixmap*;
    *cachePaint = nullptr;
    recalculateSize();
}

QPen PaintableBrick::getContourPen() { return pen; }

QList<Parameter>& PaintableBrick::getParams() { return params; }

QList<Statement> PaintableBrick::getStatements() { return statements; }

QString PaintableBrick::getMessage() { return message; }

QList<QString> PaintableBrick::getLines() { return lines; }

QWidget* PaintableBrick::getWidget() { return (QWidget*) this; }

QColor PaintableBrick::getColor() { return color; }

void PaintableBrick::paintEvent(QPaintEvent* event) {
    painter->paint(this, event);
}

void PaintableBrick::recalculateSize() {
    int newW = getWidth();
    int newH = getHeight() + PIN_H;
    
    if (*cachePaint != nullptr)
        delete *cachePaint;
    *cachePaint = nullptr;

    resize(newW, newH);
    setMinimumSize(newW, newH);
    setMaximumSize(newW, newH);
    update();
}

BrickType PaintableBrick::getType() {
    return BrickType::UNDEFINED;
}

int PaintableBrick::getWidth() {
    int w = 0;
    for (int i = 0; i < lines.count(); i++) {
        w = qMax(w, headerSize(i).width());
    }
    if (_showConfig)
        w += MARGIN + 20;
    return w;
}

bool PaintableBrick::showConfig() {
    return _showConfig;
}

QRect PaintableBrick::configRect() {
    return QRect(QPoint(getWidth() - 25, PIN_H + 5), QSize(20, 20));
}

int PaintableBrick::getHeight() {
    int h = 0;
    for (int i = 0; i < lines.count(); i++) {
        h += headerSize(i).height();
    }
    for (Statement st : statements) {
        h += st.height();
    }
    if (lines.size() == statements.count()) {
        h += BRACKET_WIDTH;
    }
    return h;
}

void PaintableBrick::addParam(Parameter param) {
    params.append(param);
    recalculateSize();
}

QPixmap** PaintableBrick::getCache() {
    return cachePaint;
}

QSize PaintableBrick::headerSize(int index) { 
    if (lines.count() <= index) return QSize(0, 0);

    QRegularExpression re("(%[0-9]+)|([a-zA-Z0-9,\\.<>=\\+\\-\\*%/]+)");
    QRegularExpressionMatchIterator i = re.globalMatch(lines.at(index));
    QFontMetrics fm(Util::font());

    int height = BRICK_MIN_HEIGHT;
    int width = MARGIN;

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.captured(1).length() > 0) { // Parametro
            int pIdx = match.captured(1).mid(1).toInt() - 1;
            if (params.size() > pIdx) {
                height = qMax(height, params[pIdx].size().height());
                width += params[pIdx].size().width() + MARGIN;
            }
        }
        else if (match.captured(2).length() > 0) { // Texto
            QString str = match.captured(2).trimmed();
            width += fm.horizontalAdvance(str) + MARGIN;
        }
    }

    height += 2 * MARGIN;
    return QSize(width, height);
}