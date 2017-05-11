#include "ContinueHolder.h"
#include "../../../../Utility/Input/InputEvent.h"


using namespace ci;
using namespace ci::app;

////////////////////////////////////////////////////////////////////////////////////////////
// 背景
////////////////////////////////////////////////////////////////////////////////////////////
tol::ContinueBackGround::ContinueBackGround()
{
}

void tol::ContinueBackGround::setup()
{
    alpha = 0.0f;

    Easing.add(alpha, 0.6f, 60, EaseType::QuintOut);
}

void tol::ContinueBackGround::update()
{
    color->setColor(0, 0, 0, alpha);
}

void tol::ContinueBackGround::draw()
{
    ci::gl::drawSolidRect(ci::Rectf(0,
                                    0,
                                    ci::app::getWindowSize().x,
                                    ci::app::getWindowSize().y));
}

////////////////////////////////////////////////////////////////////////////////////////////
// コンテニューの選択肢と文字まとめ
////////////////////////////////////////////////////////////////////////////////////////////

tol::ContinueCanvas::ContinueCanvas()
{
}

void tol::ContinueCanvas::setup()
{
    transform.position = Vec3f((float)getWindowCenter().x, -100, 0);
    color->setColor(1, 1, 1, 0.5f);

    info = std::make_shared<ContinueInfo>();
    yes_button = std::make_shared<ContinueYesButton>();
    no_button = std::make_shared<ContinueNoButton>();

    info->setup();
    yes_button->setup();
    no_button->setup();

    yes_button->transform.position = Vec3f(-200, 0, 0);
    no_button->transform.position = Vec3f(200, 0, 0);


}

void tol::ContinueCanvas::update()
{
    if (env.getPadAxis("Horizontal_Left") * -1 >= 0.2f)
    {
        yes_button->is_select = true;
        no_button->is_select = false;
    }
    if (env.getPadAxis("Horizontal_Left") * -1 <= -0.2f)
    {
        yes_button->is_select = false;
        no_button->is_select = true;
    }
    info->update();
    yes_button->update();
    no_button->update();
}

void tol::ContinueCanvas::draw()
{
    Vec2f scale = Vec2f(800, 300);
    Vec2f pos = Vec2f(-scale.x / 2, -scale.y / 1.5f);

    gl::pushMatrices();
    gl::translate(pos);
    drawRect(scale);

    gl::popMatrices();

    info->drawReflect();
    yes_button->drawReflect();
    no_button->drawReflect();
}

std::string tol::ContinueCanvas::getSelectButtonName()
{
    if (env.isPadPush(env.BUTTON_4))
    {
        if (yes_button->is_select)
        {
            if (tol::TolData.temp_coin < 5)
            {
                SoundGet.find("Gaffe")->start();
                return "";
            }

            tol::TolData.temp_coin -= 5;

            SoundGet.find("ButtonPush")->start();
            yes_button->select();
            return "Yes";
        }
        if (no_button->is_select)
        {
            SoundGet.find("ButtonPush")->start();
            no_button->select();
            return "No";
        }
    }
    return "";
}


////////////////////////////////////////////////////////////////////////////////////////////
// コンテニューまとめるやつ
////////////////////////////////////////////////////////////////////////////////////////////
tol::Continue::Continue()
{
}

void tol::Continue::setup()
{
    background = std::make_shared<ContinueBackGround>();
    canvas = std::make_shared<ContinueCanvas>();

    current_active = false;
    select_name = "";
}

void tol::Continue::update()
{
    if (current_active != player->isNotOperation())
    {
        current_active = player->isNotOperation();
        background->setup();
        canvas->setup();
        Easing.add(canvas->transform.position.y, getWindowCenter().y, 120, EaseType::BounceOut);
    }

    if (!player->isNotOperation())
        return;

    background->update();
    canvas->update();
    select_name = canvas->getSelectButtonName();
}

void tol::Continue::draw()
{
    if (!player->isNotOperation())
        return;

    background->drawReflect();
    canvas->drawReflect();
}

void tol::Continue::transDraw()
{
}