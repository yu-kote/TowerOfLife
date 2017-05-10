#include "TitleUI.h"
#include "../../GameItem/GameMainUI.h"
#include "../../../../../Utility/Utility.h"

using namespace ci;
using namespace ci::app;

////////////////////////////////////////////////////////////////////////////////////////////
// スコア文字
////////////////////////////////////////////////////////////////////////////////////////////
void tol::TitleScoreFont::setup()
{
    start_pos = Vec3f(290, 00, 0);
    setFontFromAsset("Font/nicokaku_v1.ttf", 60);
    color->setColor(ColorA::white());
}

void tol::TitleScoreFont::update()
{
    drawstring = u8"ハイスコア : " + std::to_string(TolData.high_score);
}

void tol::TitleScoreFont::draw()
{
    drawFont();
}


////////////////////////////////////////////////////////////////////////////////////////////
// スコア表示
////////////////////////////////////////////////////////////////////////////////////////////

void tol::TitleScoreIcon::setup()
{
    transform.position = Vec3f(850, HEIGHT - 50, 0);
    color->setColor(ColorA(0, 0, 0, 0.5f));

    scorefont = std::make_shared<TitleScoreFont>();
    scorefont->setup();
}

void tol::TitleScoreIcon::update()
{
    scorefont->update();
}

void tol::TitleScoreIcon::draw()
{
    drawRect(Vec2f(600, 50));
    scorefont->drawReflect();
}


////////////////////////////////////////////////////////////////////////////////////////////
// 表示
////////////////////////////////////////////////////////////////////////////////////////////

void tol::TitleUI::setup()
{
    coin = std::make_shared<CoinIcon>();
    score = std::make_shared<TitleScoreIcon>();

    coin->setup();
    score->setup();


    coin->transform.position = Vec3f(600, HEIGHT - 70, 0);
    coin->setCoin(TolData.coin);
}

void tol::TitleUI::update()
{
    coin->update();
    score->update();
}

void tol::TitleUI::transDraw()
{
    coin->drawReflect();
    score->drawReflect();
}