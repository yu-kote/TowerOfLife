#include "TitleSelect.h"

using namespace ci;
using namespace ci::app;

//////////////////////////////////////////////////////////////////////////////////
// 背景
//////////////////////////////////////////////////////////////////////////////////

void tol::TitleBackGround::setup()
{
    alpha = 0.0f;

    Easing.add(alpha, 0.6f, 60, EaseType::BackIn);
}

void tol::TitleBackGround::update()
{
    color->setColor(0, 0, 0, alpha);
}

void tol::TitleBackGround::transDraw()
{
    ci::gl::drawSolidRect(ci::Rectf(0,
                                    0,
                                    ci::app::getWindowSize().x,
                                    ci::app::getWindowSize().y));
}

//////////////////////////////////////////////////////////////////////////////////
// タイトルロゴ
//////////////////////////////////////////////////////////////////////////////////

tol::TitleLogo::TitleLogo()
    : TextureRenderer("TitleLogo")
{
    transform.scale = ci::Vec3f(1000, 250, 0);
    transform.position = -transform.scale / 2;

    transform.position.x += 30;
    transform.position.y -= 180;
}

//////////////////////////////////////////////////////////////////////////////////
// タイトルのプレイボタン
//////////////////////////////////////////////////////////////////////////////////

tol::TitlePlayButton::TitlePlayButton() :
    TextureRenderer("GotoPlayButton")
{
    is_select = true;
    current_select = is_select;
    transform.scale = ci::Vec3f(400, 200, 0);
    scale = ci::Vec3f::one() * 1.3f;
    select_scale = ci::Vec3f::one() * 1.3f;
    default_scale = ci::Vec3f::one();
}

void tol::TitlePlayButton::update()
{
    if (current_select == is_select)return;
    current_select = is_select;
    Easing.kill(scale);
    if (is_select)
        Easing.add(scale, select_scale, 10, EaseType::QuartOut);
    else
        Easing.add(scale, default_scale, 10, EaseType::QuartOut);
    SoundGet.find("ContinueSelect")->start();
}


void tol::TitlePlayButton::draw()
{
    ci::gl::translate(-scale / 2);
    ci::gl::scale(scale);
    drawRect();
}


void tol::TitlePlayButton::select()
{
    Easing.add(scale, scale * 1.1f, 60, EaseType::ElasticOut);
}

//////////////////////////////////////////////////////////////////////////////////
// まとめ
//////////////////////////////////////////////////////////////////////////////////

tol::TitleSelect::TitleSelect()
{
}

void tol::TitleSelect::setup()
{
    transform.position = Vec3f(getWindowCenter().x,
                               getWindowCenter().y,
                               0);

    logo = std::make_shared<TitleLogo>();
    play_button = std::make_shared<TitlePlayButton>();
    gachabutton = std::make_shared<TitleGachaButton>();

    logo->setup();
    play_button->setup();
    gachabutton->setup();

    play_button->transform.position.x = -300;
    gachabutton->transform.position.x = 300;
    play_button->transform.position.y = 150;
    gachabutton->transform.position.y = 150;

}

void tol::TitleSelect::update()
{
    if (env.getPadAxis("Horizontal_Left") * -1 >= 0.2f)
    {
        play_button->is_select = true;
        gachabutton->is_select = false;
    }
    if (env.getPadAxis("Horizontal_Left") * -1 <= -0.2f)
    {
        play_button->is_select = false;
        gachabutton->is_select = true;
    }

    logo->update();
    play_button->update();
    gachabutton->update();

    select_name = select();
}

void tol::TitleSelect::transDraw()
{
    logo->drawReflect();
    play_button->drawReflect();
    gachabutton->drawReflect();
}

std::string tol::TitleSelect::select()
{
    if (env.isPadPush(env.BUTTON_4))
    {
        if (play_button->is_select)
        {
            SoundGet.find("ButtonPush")->start();
            play_button->select();
            return "Play";
        }
        if (gachabutton->is_select)
        {
            if (tol::TolData.coin < 5)
            {
                SoundGet.find("Gaffe")->start();
                return "";
            }
            tol::TolData.coin -= 5;
            SoundGet.find("ButtonPush")->start();
            gachabutton->select();
            return "Gacha";
        }
    }
    return "";
}



