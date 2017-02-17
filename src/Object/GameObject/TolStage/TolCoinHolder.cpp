#include "TolCoinHolder.h"
#include <random>
#include "../../../Utility/Utility.h"
#include "../../../Task/SoundManager.h"
#include "../../../Tol/TolGameDataManager.h"

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

void tol::TolCoinHolder::instanceCoin(const ci::Vec2f& pos, const float& height, int coin_amount_)
{
    std::shared_ptr<TolCoin> coin = std::make_shared<TolCoin>();
    coin->transform.position = Vec3f(pos.x, height, pos.y);
    coin->coin_amount = coin_amount_;
    coin->setup();

    coins.push_back(std::move(coin));
}

void tol::TolCoinHolder::reset()
{
    coins.clear();
}

void tol::TolCoinHolder::playerGetCoins()
{
    for (auto it = coins.begin(); it != coins.end();)
    {
        if ((*it)->isHitToCoin(player->transform.position))
        {
            SoundGet.find("Coin")->start();
            TolData.coin += (*it)->coin_amount;
            it = coins.erase(it);
            continue;
        }
        it++;
    }
}
