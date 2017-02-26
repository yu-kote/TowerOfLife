#include "Title.h"

#include "../../Scene/Manager/SceneManager.h"
#include "../../Task/SoundManager.h"

#include "../../Object/UI/UICamera/UICamera.h"
#include "../../Object/UI/TolUI/BackGround/BlocksBackGround.h"
#include "../../Object/UI/TolUI/Fade/Fade.h"
#include "../../Object/UI/TolUI/Title/TitleSelect.h"


Title::Title()
{
}

void Title::setup()
{
    ui_entities.instantiate<tol::UICamera>();
    ui_entities.instantiate<tol::BlocksBackGround>();

    ui_entities.instantiate<tol::TitleSelect>();

    ui_entities.instantiate<tol::FadeIn>(tol::FadeIn(ci::ColorA(0, 0, 0, 1), 60));

    ui_entities.instantiate<tol::FadeOut>(tol::FadeOut(ci::ColorA(0, 0, 0, 0), 120));

    ui_entities.getInstance<tol::FadeIn>()->fadeStart();

    SoundGet.find("TitleBGM")->start();

    entities.setup();
    ui_entities.setup();

    select_name = "";
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
    if (select_name == "")
    {
        select_name = ui_entities.getInstance<tol::TitleSelect>()->getSelectButtonName();
        return;
    }
    ui_entities.getInstance<tol::TitleSelect>()->setIsUpdateActive(false);
    ui_entities.getInstance<tol::FadeOut>()->fadeStart();
    if (!ui_entities.getInstance<tol::FadeOut>()->isFadeEnd())
        return;
    entities.allDestroy();
    ui_entities.allDestroy();
    Easing.allClear();
    SoundGet.allStop();

    tol::TolData.prev_scene = SceneCategory::TITLE;
    if (select_name == "Play")
        SceneCreate<GameMain>(new GameMain());
    else if (select_name == "Gacha")
        SceneCreate<Gacha>(new Gacha());
    SceneManager::instance().get().setup();
}

void Title::shutdown()
{
    entities.allDestroy();
    ui_entities.allDestroy();
}
