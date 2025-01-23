#pragma once

#include <QtCore>
#include <QDialog>
#include "LineEdit.h"

class ModalNewVariable : public QDialog {
private:
    LineEdit* lineEditVar;
    QComboBox* comboTypes;
    bool rejected;
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
public:
    ModalNewVariable(QWidget* parent);
    QString getText();
    QString getType();
    void lineEditDone();
};