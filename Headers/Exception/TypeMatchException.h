#pragma once

#include <QException>

class TypeMatchException {
    private:
        QString err_message;

    public:
        TypeMatchException(const char* message) { err_message = QString(message); };
        void raise() { throw *this; };
        QString what() { return err_message; }
};