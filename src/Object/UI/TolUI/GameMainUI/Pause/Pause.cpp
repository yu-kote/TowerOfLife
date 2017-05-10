#include "Pause.h"

using namespace ci;
using namespace ci::app;

////////////////////////////////////////////////////////////////////////////////////////////
// 背景
////////////////////////////////////////////////////////////////////////////////////////////

void tol::PauseBackGround::setup()
{
    color->setColor(0, 0, 0, 0.6f);
}

void tol::PauseBackGround::update()
{
}

void tol::PauseBackGround::draw()
{
    ci::gl::drawSolidRect(ci::Rectf(0,
                                    0,
                                    ci::app::getWindowSize().x,
                                    ci::app::getWindowSize().y));
}


////////////////////////////////////////////////////////////////////////////////////////////
// ポーズの文字
////////////////////////////////////////////////////////////////////////////////////////////

void tol::PauseFont::setup()
{
    drawstring = u8"一時停止";
    setFontFromAsset("Font/HuiFont29.ttf", 100);
    transform.position = Vec3f(getWindowCenter().x,
                               getWindowCenter().y - font.getSize() / 2,
                               0);
}

void tol::PauseFont::update()
{
}

void tol::PauseFont::draw()
{
    drawFontCenter();
}

////////////////////////////////////////////////////////////////////////////////////////////
// 表示
////////////////////////////////////////////////////////////////////////////////////////////

void tol::Pause::setup()
{
    background = std::make_shared<PauseBackGround>();
    font = std::make_shared<PauseFont>();

    background->setup();
    font->setup();

    // 最初は停止させないためアクティブを切る
    setDrawActive(false);
}

void tol::Pause::update()
{
    background->update();
    font->update();
}

void tol::Pause::draw()
{
    background->drawReflect();
    font->drawReflect();
}
