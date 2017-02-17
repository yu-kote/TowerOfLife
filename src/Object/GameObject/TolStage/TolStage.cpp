#include "TolStage.h"
#include "../../../Task/SoundManager.h"
#include "../../../Utility/Input/InputEvent.h"

void tol::TolStage::setup()
{
    block_holder = std::make_shared<tol::TolBlockHolder>();
    coin_holder = std::make_shared<tol::TolCoinHolder>();

    block_holder->setPlayer(player);
    block_holder->setCamera(camera);
    block_holder->setCoinHolder(coin_holder);
    block_holder->setup();

    coin_holder->setPlayer(player);
    coin_holder->setup();

}

void tol::TolStage::update()
{
    block_holder->update();
    coin_holder->update();

    if (player->isDead())
    {
        block_holder->reset();
        coin_holder->reset();
    }

    if (env.isPush(ci::app::KeyEvent::KEY_0))
        test = !test;

    if (test)
    {
        if (!SoundGet.find("tower_bgm1")->isEnabled())
            SoundGet.find("tower_bgm1")->start();
    }
    else
    {
        SoundGet.find("tower_bgm1")->disable();
    }
}

void tol::TolStage::laterUpdate()
{
    block_holder->laterUpdate();
    coin_holder->laterUpdate();
}

void tol::TolStage::draw()
{
    block_holder->draw();
    coin_holder->draw();
}

void tol::TolStage::transDraw()
{
    block_holder->transDraw();
    coin_holder->transDraw();
}

void tol::TolStage::laterDraw()
{
    block_holder->laterDraw();
    coin_holder->laterDraw();
}


