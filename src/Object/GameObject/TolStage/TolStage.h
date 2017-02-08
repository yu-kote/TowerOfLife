#pragma once
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockHolder.h"

namespace tol
{
    class TolStage : public GameObject
    {
    public:
        TolStage() {}

        void setup()override;
        void update()override;
        void draw()override;

    private:

        TolBlockHolder block_holder;


    };
}