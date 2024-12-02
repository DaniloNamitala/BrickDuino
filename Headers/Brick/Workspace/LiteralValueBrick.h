#pragma once

#include <QtCore>
#include <QtWidgets>
#include <QLineEdit>
#include "ValueBrick.h"	

class LineEdit : public QLineEdit {

public:
    LineEdit(QWidget* parent = nullptr) : QLineEdit(parent) {}

protected:
    void keyReleaseEvent(QKeyEvent* event) override {
        QLineEdit::keyReleaseEvent(event);
        if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Return) {
            emit editingFinished();
        }
    }
};

namespace Workspace {
    class LiteralValueBrick : public Workspace::ValueBrick
    {
        private:
            LineEdit* lineEdtMessage;

            void lineEditChanged(const QString& text);
            void lineEditDone();
        protected:
            int getHeight() override;
            int getWidth() override;
        public:
            LiteralValueBrick(QWidget* parent, const char* message, const char* name, QColor color);
            LiteralValueBrick(const char* message, const char* name, QColor color);
            BrickType getType() override;

            void mouseDoubleClickEvent(QMouseEvent* event);
    };
};