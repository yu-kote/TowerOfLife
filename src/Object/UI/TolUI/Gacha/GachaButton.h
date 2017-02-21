#pragma once
#include "../../Button/ButtonBase.h"



namespace tol
{
    class GachaButton : public tol::ButtonBase
    {
    public:

        GachaButton();
        void setup()override;
        void update()override;
        void draw()override;

    private:

        std::vector<ci::Vec2f> points;

    };


}