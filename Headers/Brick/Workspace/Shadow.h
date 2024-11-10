#include "WorkspaceBrick.h"

namespace Workspace {
    class Shadow : public Workspace::Brick {
        private:
            BrickType type; 
        public:
            Shadow(QWidget* parent);
            int getWidth() override;
    };
};