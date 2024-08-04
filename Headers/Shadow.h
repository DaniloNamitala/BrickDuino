#include "FunctionBrick.h"

class Shadow : public FunctionBrick { 
    public:
        Shadow(QWidget* parent);
        virtual int getWidth() override;
};