#pragma once
#include "../Object.h"
#include "../Component/Components/Transform.h"

namespace tol
{
    class Component : public Object
    {
    public:
        virtual void setup() {}

        virtual void update() {}

        virtual void drawBegin() {}
        virtual void drawEnd() {}
        virtual void draw() {}

    protected:

    private:

    };

}
