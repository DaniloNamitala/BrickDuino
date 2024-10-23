#pragma once

namespace Workspace {
    class Brick;
};

class Statement {
    private:
        Workspace::Brick* _head;
    public:
        Statement();
        void insert(Workspace::Brick* brick);
        void remove(Workspace::Brick* brick);
        Workspace::Brick* head();
        Workspace::Brick* tail();
        int height();
};