#pragma once
#include "../GameObject.h"
#include "TolBlockHolder.h"
#include "TolCoinHolder.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"

namespace tol
{

    enum GameLevel
    {
        LEVEL_1,
        LEVEL_2,
        LEVEL_3,
    };

    class TolStage : public GameObject
    {
    public:
        TolStage() {}

        void setup()override;
        void update()override;
        void laterUpdate()override;
        void draw()override;
        void transDraw()override;
        void laterDraw()override;

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }
        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }

    private:

        std::shared_ptr<tol::Camera> camera;
        std::shared_ptr<tol::Player> player;

        std::shared_ptr<tol::TolBlockHolder> block_holder;
        std::shared_ptr<tol::TolCoinHolder> coin_holder;

    private:



        GameLevel level;

        bool test = true;

    };
}