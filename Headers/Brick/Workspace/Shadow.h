#include "WorkspaceBrick.h"

namespace Workspace {
    class Shadow : public Workspace::Brick {
        private:
            BrickType type; 
        public:
            Shadow(QWidget* parent, bool value);
            int getWidth() override;
            int getHeight() override;
            BrickType getType() override;
            void move(const QPoint& pos) override;
    };
};