#pragma once

#include <QtCore>
#include <QDialog>
#include "LineEdit.h"

class ModalNewVariable : public QDialog {
private:
    LineEdit* lineEditVar;
    bool rejected;
protected:
    void keyPressEvent(QKeyEvent* event) override;
public:
    ModalNewVariable(QWidget* parent);
    QString getText();
    void lineEditDone();
};