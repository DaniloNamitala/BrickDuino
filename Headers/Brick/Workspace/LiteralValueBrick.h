#pragma once

#include <QtCore>
#include <QtWidgets>
#include <QLineEdit>
#include "ValueBrick.h"	
#include "LineEdit.h"

namespace Workspace {
    class LiteralValueBrick : public Workspace::ValueBrick
    {
        private:
            LineEdit* lineEdtMessage;

            void lineEditChanged(const QString& text);
            void lineEditDone();
            void lineEditReject();
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