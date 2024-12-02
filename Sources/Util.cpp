#include "Util.h"
#include <QFontMetrics>
#include <QFont>
#include <QString>
#include <QtWidgets>

QSize Util::textSize(QString text, QFont font) {
    QFontMetrics fm(font);
    return QSize(fm.horizontalAdvance(text), fm.height());
}

QPen Util::contourPen(QColor color) {
    QPen pen(color.darker(300));
    pen.setWidth(2);
    return pen;
}

QPen Util::textPen() {
    QPen textPen(QColor(255, 255, 255));
    textPen.setWidth(3);
    return textPen;
}

QFont Util::font() {
    return QFont("Cascadia Code", 10, QFont::Bold, false);
}

QFont Util::font_sm() {
    return QFont("Cascadia Code", 10, QFont::Bold, false);
}