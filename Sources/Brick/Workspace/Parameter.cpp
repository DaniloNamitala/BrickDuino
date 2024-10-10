#include "Parameter.h"
#include "Util.h"
#include "TypeMatchException.h"

Parameter::Parameter(QString textBefore, QString textAfter, ValueType type) {
    this->textBefore = textBefore;
    this->textAfter = textAfter;
    this->type = type;
}

Parameter::Parameter(ValueType type) {
    this->textBefore = "";
    this->textAfter = "";
    this->type = type;
}

Parameter::Parameter(QString textBefore, ValueType type) {
    this->textBefore = textBefore;
    this->textAfter = "";
    this->type = type;
}

QSize Parameter::size(QFont font) {
    int width = !value.isEmpty() ? value.size().width() : EMPTY_VALUE_WIDTH;
    QFontMetrics fm(font);
    if (!textBefore.isEmpty()) width +=  fm.horizontalAdvance(textBefore) + MARGIN;
    if (!textAfter.isEmpty()) width +=  fm.horizontalAdvance(textAfter) + MARGIN;

    int height = !value.isEmpty() ? value.size().height() : EMPTY_VALUE_HEIGHT;
    if (!textBefore.isEmpty() || !textAfter.isEmpty())
        height = qMax(height, fm.height());
        
    return QSize(width, height);
}

void Parameter::paint(QPainter* painter, QPoint origin) {
    painter->save();
    painter->translate(origin);

    QPainterPath path2;
    int x = 0;

    if (!textBefore.isEmpty()) {
        x = Util::textSize(textBefore, Util::font()).width() + MARGIN;
        painter->save();
        painter->setPen(Util::textPen());
        painter->drawText(0, 0 + Util::textSize(textBefore, Util::font()).height(), textBefore);
        painter->restore();
    }

    if (value.isEmpty()) {
        path2.moveTo(x + (EMPTY_VALUE_HEIGHT / 2) , 0);
        path2.arcTo(x, 0, EMPTY_VALUE_HEIGHT, EMPTY_VALUE_HEIGHT, 90, 180);
        path2.lineTo(x + EMPTY_VALUE_WIDTH - (EMPTY_VALUE_HEIGHT / 2), 0 + EMPTY_VALUE_HEIGHT);
        path2.arcTo(x + EMPTY_VALUE_WIDTH - EMPTY_VALUE_HEIGHT, 0, EMPTY_VALUE_HEIGHT, EMPTY_VALUE_HEIGHT, 270, 180);
        path2.lineTo(x + (EMPTY_VALUE_HEIGHT / 2), 0);

        painter->setBrush(painter->brush().color().darker(150));
        painter->drawPath(path2);
    } else {
        value.paint(painter, QPoint(x, 0));
    }



    if (!textAfter.isEmpty()) {
        x += EMPTY_VALUE_WIDTH + MARGIN;
        painter->save();
        painter->setPen(Util::textPen());
        painter->drawText(x, 0 + Util::textSize(textAfter, Util::font()).height(), textAfter);
        painter->restore();
    }
    
    painter->translate(-origin);
    painter->restore();
}

void Parameter::setValue(Value value) {
    if (type != value.getType())
        throw new TypeMatchException("Value and parameter type doesn't match!");
    this->value = value;
}