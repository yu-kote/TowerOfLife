#include "TitleSelect.h"

using namespace ci;
using namespace ci::app;


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
}

void tol::TitleSelect::transDraw()
{
    logo->drawReflect();
    play_button->drawReflect();
    gachabutton->drawReflect();
}

std::string tol::TitleSelect::getSelectButtonName()
{
    if (env.isPadPush(env.BUTTON_4))
    {
        SoundGet.find("ButtonPush")->start();
        if (play_button->is_select)
        {
            play_button->select();
            return "Play";
        }
        if (gachabutton->is_select)
        {
            gachabutton->select();
            return "Gacha";
        }
    }
    return "";
}
