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
    ui_entities.instantiate<tol::FadeOut>(tol::FadeOut(ci::ColorA(0, 0, 0, 0), 120));

    ui_entities.getInstance<tol::GachaHolder>()->setFadeIn(ui_entities.getInstance<tol::FadeIn>());

    ui_entities.getInstance<tol::FadeIn>()->fadeStart();

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
    if (!ui_entities.getInstance<tol::GachaHolder>()->isGachaEnd())return;
    ui_entities.getInstance<tol::FadeOut>()->fadeStart();
    if (ui_entities.getInstance<tol::FadeOut>()->isFadeEnd())
    {
        entities.allDestroy();
        ui_entities.allDestroy();
        Easing.allClear();
        SoundGet.allStop();

        if (tol::TolData.prev_scene == SceneCategory::GAMEMAIN)
            SceneCreate<GameMain>(new GameMain());
        else if(tol::TolData.prev_scene == SceneCategory::TITLE)
            SceneCreate<Title>(new Title());
        tol::TolData.prev_scene = SceneCategory::GACHA;
        SceneManager::instance().get().setup();
    }
}

void Gacha::shutdown()
{
    entities.allDestroy();
    ui_entities.allDestroy();
}
