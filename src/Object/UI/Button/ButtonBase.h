#pragma once
#include "../UIBase.h"


namespace tol
{
    class ButtonBase : public tol::UIBase
    {
    public:

        virtual void onClick() = 0;

    protected:

        std::function<bool> colision;
        ci::gl::TextureRef tex;

        float radius;


    };
}
