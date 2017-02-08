#pragma once
#include "cinder/app/App.h"
#include "../GameObject.h"


namespace tol
{
    class TolBlock;
    class TolBlockActionBase
    {
    public:
        TolBlockActionBase(TolBlock* block_);

        virtual void setup() {}

        virtual void fall() {}
        virtual void update() {}


    protected:
        TolBlock* block;
        ci::Vec3f start_pos;
    };
}