#include "Parameter.h"
#include "Brick.h"
#include "Util.h"

Parameter::Parameter(QString textBefore, QString textAfter, ParamType type) {
    this->textBefore = textBefore;
    this->textAfter = textAfter;
    this->type = type;
}

QSize Parameter::size(QFont font) {
    int width = EMPTY_VALUE_WIDTH;
    QFontMetrics fm(font);
    if (!textBefore.isEmpty()) width +=  fm.horizontalAdvance(textBefore) + MARGIN;
    if (!textAfter.isEmpty()) width +=  fm.horizontalAdvance(textAfter) + MARGIN;

    int height = EMPTY_VALUE_HEIGHT;
    if (!textBefore.isEmpty() || !textAfter.isEmpty())
        height = qMax(height, fm.height());
        
    return QSize(width, height);
}

void Parameter::paint(QPainter* painter, QPoint origin) {
    painter->save();
    QPainterPath path2;
    int x = origin.x();
    if (!textBefore.isEmpty()) {
        painter->save();
        painter->setPen(Brick::getTextPen());
        painter->drawText(origin.x(), origin.y() + Util::textSize(textBefore, Brick::getFont()).height(), textBefore);
        x += Util::textSize(textBefore, Brick::getFont()).width() + MARGIN;
        painter->restore();
    }

    path2.moveTo(x + (EMPTY_VALUE_HEIGHT / 2) , origin.y());
    path2.arcTo(x, origin.y(), EMPTY_VALUE_HEIGHT, EMPTY_VALUE_HEIGHT, 90, 180);
    path2.lineTo(x + EMPTY_VALUE_WIDTH - (EMPTY_VALUE_HEIGHT / 2), origin.y() + EMPTY_VALUE_HEIGHT);
    path2.arcTo(x + EMPTY_VALUE_WIDTH - EMPTY_VALUE_HEIGHT, MARGIN, EMPTY_VALUE_HEIGHT, EMPTY_VALUE_HEIGHT, 270, 180);
    path2.lineTo(x + (EMPTY_VALUE_HEIGHT / 2), origin.y());

    painter->setBrush(painter->brush().color().darker(150));
    painter->drawPath(path2);

    if (!textAfter.isEmpty()) {
        x += EMPTY_VALUE_WIDTH + MARGIN;
        painter->save();
        painter->setPen(Brick::getTextPen());
        painter->drawText(x, origin.y() + Util::textSize(textAfter, Brick::getFont()).height(), textAfter);
        painter->restore();
    }
    painter->restore();
}