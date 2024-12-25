#pragma once

#include <QtCore>
#include <QLineEdit>
#include <QKeyEvent>


class LineEdit : public QLineEdit {
private:
    QString initialText;
public:
    LineEdit(QWidget* parent = nullptr);
    void escPressed();
protected:
    void keyReleaseEvent(QKeyEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;
};