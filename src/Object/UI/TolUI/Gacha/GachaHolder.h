#pragma once
#include "../../../GameObject/GameObject.h"
#include "../../../GameObject/Player/Player.h"
#include "../../TolUI/Fade/Fade.h"

#include "GachaButton.h"
#include "GachaItem.h"

namespace tol
{
    class GachaHolder : public tol::GameObject
    {
    public:

        void setup()override;
        void update()override;
        void draw()override;

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }
        void setFadeIn(std::shared_ptr<tol::FadeIn> fade) { fadein = fade; }

    private:
        std::shared_ptr<tol::Player> player;
        std::shared_ptr<tol::FadeIn> fadein;


    private:

        std::shared_ptr<GachaButton> gachabutton;
        std::shared_ptr<GachaItem> item;


    };
}
