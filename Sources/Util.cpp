#include "Util.h"
#include <QFontMetrics>
#include <QFont>
#include <QString>
#include <QtWidgets>

QSize Util::textSize(QString text, QFont font) {
    QFontMetrics fm(font);
    return QSize(fm.horizontalAdvance(text), fm.height());
}