#pragma once
#include "../GameObject.h"
#include "TolCoin.h"
#include "../Player/Player.h"



namespace tol
{
    class TolCoinHolder : public TolCoin
    {
    public:

        TolCoinHolder() {}

        void setup()override;
        void update()override;
        void draw()override;

        void setPlayer(std::shared_ptr<tol::Player> player_) { player = player_; }


        void instanceCoin(const ci::Vec2f& pos, const float& height, CoinType coin_type);

    private:
        std::shared_ptr<tol::Player> player;

        void playerGetCoins();

        std::list<std::shared_ptr<tol::TolCoin>> coins;

    };
}