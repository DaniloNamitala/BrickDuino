#pragma once

#include <QtCore>

namespace Util {
    QSize textSize(QString text, QFont font);
    QPen contourPen(QColor color);
    QPen textPen();
    QFont font();
    QFont font_sm();
};