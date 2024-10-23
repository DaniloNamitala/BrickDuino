#include "Statement.h"
#include "WorkspaceBrick.h"

/*---------------- STATMENT -------------------------*/

Statement::Statement() {
    _head = nullptr;
}

void Statement::insert(Workspace::Brick* brick) {
    this->_head = brick;
}

void Statement::remove(Workspace::Brick* brick) {
    if (_head == brick) {
        _head = nullptr;
        return;
    }
}

Workspace::Brick* Statement::head() {
    return _head;
}

Workspace::Brick* Statement::tail() {
    return _head->tail();
}

int Statement::height() {
    if (_head == nullptr) return EMPTY_STATEMENT_GAP;

    int height = 0;
    Workspace::Brick* actual = _head;
    do {
        height += actual->size().height();
        actual = actual->getNext();
    } while (actual != nullptr);

    return height;
}