#include "Title.h"

#include "../../Scene/Manager/SceneManager.h"
#include "../../Task/SoundManager.h"

#include "../../Object/UI/UICamera/UICamera.h"
#include "../../Object/UI/TolUI/BackGround/BlocksBackGround.h"
#include "../../Object/UI/TolUI/Fade/Fade.h"

Title::Title()
{
}

void Title::setup()
{
    ui_entities.instantiate<tol::UICamera>();
    ui_entities.instantiate<tol::BlocksBackGround>();
    ui_entities.instantiate<tol::FadeIn>(tol::FadeIn(ci::ColorA(0, 0, 0, 1), 60));


    entities.setup();
    ui_entities.setup();
}

void Title::update()
{
    entities.update();
    ui_entities.update();
}

#include "GameMain.h"
#include "Gacha.h"

void Title::draw()
{
    entities.draw();
    ui_entities.draw();
}

void Title::shift()
{

}

void Title::shutdown()
{
    entities.allDestroy();
    ui_entities.allDestroy();
}
