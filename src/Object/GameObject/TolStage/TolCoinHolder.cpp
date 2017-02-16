#include "TolCoinHolder.h"
#include <random>
#include "../../../Utility/Utility.h"
#include "../../../Task/SoundManager.h"

using namespace ci;
using namespace ci::app;

void tol::TolCoinHolder::setup()
{
}

void tol::TolCoinHolder::update()
{
    playerGetCoins();
    for (auto& it : coins)
        (*it).update();
}

void tol::TolCoinHolder::draw()
{
    pushModelView();
    for (auto& it : coins)
        (*it).draw();
    popModelView();
}

void tol::TolCoinHolder::instanceCoin(const ci::Vec2f& pos, const float& height, CoinType coin_type)
{
    std::shared_ptr<TolCoin> coin = std::make_shared<TolCoin>();
    coin->transform.position = Vec3f(pos.x, height, pos.y);
    coin->coin_type = coin_type;
    coin->setup();

    coins.push_back(std::move(coin));
}

void tol::TolCoinHolder::playerGetCoins()
{
    for (auto it = coins.begin(); it != coins.end();)
    {
        if ((*it)->isHitToCoin(player->transform.position))
        {
            SoundGet.find("Coin")->start();
            it = coins.erase(it);
            continue;
        }
        it++;
    }
}
