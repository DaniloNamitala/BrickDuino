#include "FunctionBrick.h"

namespace Workspace {
    class Shadow : public Workspace::FunctionBrick { 
        public:
            Shadow(QWidget* parent);
            int getWidth() override;
    };
};