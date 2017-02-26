#pragma once
#include "../../Button/ButtonBase.h"
#include "../../../Component/Components/Color.h"


namespace tol
{
    class GachaButton : public tol::ButtonBase
    {
    public:

        GachaButton();
        void setup()override;
        void update()override;
        void draw()override;

        void setPolygon(const std::vector<ci::Vec2f>& vartex);

    private:

        std::vector<ci::Vec2f> points;

    };


}