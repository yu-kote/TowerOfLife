#include "GameMain.h"
#include "../../Tol/TolGameDataManager.h"

#include "../../Scene/Manager/SceneManager.h"
#include "../../Task/SoundManager.h"

#include "../../Object/GameObject/Light/Light.h"
#include "../../Object/GameObject/Camera/Camera.h"
#include "../../Object/GameObject/Skydome/Skydomes.h"
#include "../../Object/GameObject/Player/Player.h"
#include "../../Object/GameObject/TolStage/TolStage.h"

#include "../../Object/UI/UICamera/UICamera.h"
#include "../../Object/UI/FrameView/FrameRateView.h"
#include "../../Object/UI/TolUI/Fade/Fade.h"
#include "../../Object/UI/TolUI/Continue/ContinueHolder.h"
#include "../../Object/UI/TolUI/GameItem/ItemHolder.h"


GameMain::GameMain()
{
}

void GameMain::setup()
{
    // インスタンスを作るところ
    // 3D Objcts
    entities.instantiate<tol::Light>();
    entities.instantiate<tol::Camera>();
    entities.instantiate<tol::UniverseSkydome>();
    entities.instantiate<tol::EarthSkydome>();
    entities.instantiate<tol::Player>();
    entities.instantiate<tol::PlayerShadow>();
    entities.instantiate<tol::DebugDraw>();
    entities.instantiate<tol::TolStage>();

    // UI
    ui_entities.instantiate<tol::UICamera>();
    ui_entities.instantiate<tol::FrameRateView>();
    ui_entities.instantiate<tol::FadeIn>(tol::FadeIn(ci::ColorA(0, 0, 0, 1), 120));
    ui_entities.getInstance<tol::FadeIn>()->fadeStart();
    ui_entities.instantiate<tol::Continue>();
    ui_entities.instantiate<tol::FadeOut>(tol::FadeOut(ci::ColorA(0, 0, 0, 0), 120));
    ui_entities.instantiate<tol::ItemHolder>();



    // インスタンスをもらってポインタを渡すところ
    // 3D Objcts
    entities.getInstance<tol::EarthSkydome>()->setTerget(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::UniverseSkydome>()->setTerget(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::Player>()->setCamera(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::TolStage>()->setPlayer(entities.getInstance<tol::Player>());
    entities.getInstance<tol::TolStage>()->setCamera(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::PlayerShadow>()->setPlayer(entities.getInstance<tol::Player>());
    entities.getInstance<tol::DebugDraw>()->setPlayer(entities.getInstance<tol::Player>());
    entities.getInstance<tol::DebugDraw>()->setCamera(entities.getInstance<tol::Camera>());

    // UI
    ui_entities.getInstance<tol::Continue>()->setPlayer(entities.getInstance<tol::Player>());

    entities.setup();
    ui_entities.setup();
    select_name = "";
}

void GameMain::update()
{
    entities.update();
    ui_entities.update();
}

void GameMain::draw()
{
    entities.draw();
    ui_entities.draw();
}

#include "Gacha.h"
#include "Title.h"

void GameMain::shift()
{
    if (!entities.getInstance<tol::Player>()->isNotOperation())return;
    if (select_name == "")
    {
        select_name = ui_entities.getInstance<tol::Continue>()->getSelectButtonName();
        return;
    }
    ui_entities.getInstance<tol::Continue>()->setIsUpdateActive(false);
    ui_entities.getInstance<tol::FadeOut>()->fadeStart();
    if (!ui_entities.getInstance<tol::FadeOut>()->isFadeEnd())
        return;
    entities.allDestroy();
    ui_entities.allDestroy();
    Easing.allClear();
    SoundGet.allStop();

    tol::TolData.prev_scene = SceneCategory::GAMEMAIN;
    if (select_name == "Yes")
        SceneCreate<Gacha>(new Gacha());
    else if (select_name == "No")
        SceneCreate<Title>(new Title());
    SceneManager::instance().get().setup();
}

void GameMain::shutdown()
{
    entities.allDestroy();
    ui_entities.allDestroy();
}
