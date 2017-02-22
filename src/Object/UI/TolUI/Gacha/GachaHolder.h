#pragma once
#include "../../../GameObject/GameObject.h"
#include "GachaButton.h"
#include "../../../GameObject/Player/Player.h"

namespace tol
{
    class GachaHolder : public tol::GameObject
    {
    public:

        void setup()override;
        void update()override;
        void draw()override;

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }

    private:

        //std::shared_ptr<tol::Camera> camera;
        std::shared_ptr<tol::Player> player;

        std::shared_ptr<GachaButton> gachabutton;

    };
}
