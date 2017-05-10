#include "TolStage.h"
#include "../../../Task/SoundManager.h"
#include "../../../Utility/Input/InputEvent.h"

using namespace ci;
using namespace ci::app;

tol::TolStage::TolStage()
{
    block_holder = std::make_shared<tol::TolBlockHolder>();
    coin_holder = std::make_shared<tol::TolCoinHolder>();
}

void tol::TolStage::setup()
{
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


