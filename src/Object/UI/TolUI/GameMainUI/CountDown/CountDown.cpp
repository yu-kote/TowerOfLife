#include "CountDown.h"

#include "../../../../../Task/SoundManager.h"

using namespace ci;
using namespace ci::app;

// 秒数はあえて60フレームじゃないほうがいい気がする
int seconds()
{
    return  70;
}

tol::CountDown::CountDown()
{
}

void tol::CountDown::setup()
{
    count_down_start_frame = 100;
    current_countdown_state = isCountDownStart();

    // 3からスタート
    drawcount = 3;
    frame_count = drawcount * seconds();

    drawstring = std::to_string(drawcount);

    // サイズはちょうどいい感じに
    setFontFromAsset("Font/HuiFont29.ttf", 450);

    // 少し上に表示してみる
    transform.position = Vec3f(getWindowCenter().x,
                               getWindowCenter().y - font.getSize() / 2 - 50,
                               0);
    transform.scale = Vec3f(1, 0.8f, 1);

    color->setColor(ColorA::black());
}

void tol::CountDown::update()
{
    count_down_start_frame--;
    if (current_countdown_state != isCountDownStart())
    {
        current_countdown_state = isCountDownStart();
        SoundGet.find("CountDown")->start();
    }

    if (isCountDownStart() == false)
        return;

    countUpdate();
}

void tol::CountDown::draw()
{
    if (isCountDownStart() == false)
        return;
    drawFontCenter();
}

bool tol::CountDown::isCountDownEnd()
{
    return frame_count < 0;
}

void tol::CountDown::countUpdate()
{
    if (isCountDownEnd())
        return;

    frame_count--;

    if (frame_count % seconds() != 0)
        return;

    drawcount -= 1;
    if (drawcount > 0)
    {
        SoundGet.find("CountDown")->start();
        drawstring = std::to_string(drawcount);
    }
    else
        drawstring = "";
}

bool tol::CountDown::isCountDownStart()
{
    return count_down_start_frame < 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
// 表示
////////////////////////////////////////////////////////////////////////////////////////////
tol::CountDownCanvas::CountDownCanvas()
{
}

void tol::CountDownCanvas::setup()
{
    countdown = std::make_shared<CountDown>();
    countdown->setup();

    is_start = false;
}

void tol::CountDownCanvas::update()
{
    countdown->update();
}

void tol::CountDownCanvas::draw()
{
    countdown->drawReflect();
}

