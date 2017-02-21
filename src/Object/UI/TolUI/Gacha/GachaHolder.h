#pragma once
#include "../../../GameObject/GameObject.h"
#include "GachaButton.h"

namespace tol
{
    class GachaHolder : public tol::GameObject
    {
    public:

        void setup()override;
        void update()override;
        void draw()override;


    private:

        //std::shared_ptr<tol::Camera> camera;
        //std::shared_ptr<tol::Player> player;

        std::shared_ptr<GachaButton> gachabutton;

    };
}
