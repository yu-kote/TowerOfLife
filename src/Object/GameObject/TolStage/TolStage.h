#pragma once
#include "../GameObject.h"
#include "TolBlock.h"
#include "TolBlockHolder.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"

namespace tol
{
    class TolStage : public GameObject
    {
    public:
        TolStage() {}

        void setup()override;
        void update()override;
        void draw()override;

        void setCamera(std::shared_ptr<tol::Camera> camera_) { camera = camera_; }
        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }

    private:

        TolBlockHolder block_holder;
        std::shared_ptr<tol::Camera> camera;
        std::shared_ptr<tol::Player> player;

    };
}