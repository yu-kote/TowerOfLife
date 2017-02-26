#include "Gacha.h"
#include "../../Tol/TolGameDataManager.h"

#include "../../Scene/Manager/SceneManager.h"
#include "../../Task/SoundManager.h"

#include "../../Object/UI/UICamera/UICamera.h"
#include "../../Object/UI/TolUI/Gacha/GachaHolder.h"
#include "../../Object/UI/TolUI/BackGround/BlocksBackGround.h"
#include "../../Object/UI/TolUI/Fade/Fade.h"


Gacha::Gacha()
{
}

void Gacha::setup()
{
    // UI
    ui_entities.instantiate<tol::UICamera>();
    ui_entities.instantiate<tol::BlocksBackGround>();
    ui_entities.instantiate<tol::GachaHolder>();
    ui_entities.instantiate<tol::FadeIn>(tol::FadeIn(ci::ColorA(0, 0, 0, 1), 120));


    ui_entities.getInstance<tol::GachaHolder>()->setFadeIn(ui_entities.getInstance<tol::FadeIn>());

    entities.setup();
    ui_entities.setup();
}

void Gacha::update()
{
    entities.update();
    ui_entities.update();
}

void Gacha::draw()
{
    entities.draw();
    ui_entities.draw();
}

#include "GameMain.h"
#include "Title.h"

void Gacha::shift()
{
    if (env.isPush(ci::app::KeyEvent::KEY_1))
    {
        SoundGet.allStop();
        entities.allDestroy();
        ui_entities.allDestroy();

        if (tol::TolData.prev_scene == SceneCategory::GAMEMAIN)
            SceneCreate<GameMain>(new GameMain());

        tol::TolData.prev_scene = SceneCategory::GACHA;
        SceneManager::instance().get().setup();
    }
}

void Gacha::shutdown()
{
    entities.allDestroy();
    ui_entities.allDestroy();
}
