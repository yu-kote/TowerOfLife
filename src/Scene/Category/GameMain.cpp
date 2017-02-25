#include "GameMain.h"

#include "../../Scene/Manager/SceneManager.h"
#include "../../Task/SoundManager.h"

#include "../../Object/GameObject/Light/Light.h"
#include "../../Object/GameObject/Camera/Camera.h"
#include "../../Object/GameObject/Skydome/Skydomes.h"
#include "../../Object/GameObject/Player/Player.h"
#include "../../Object/GameObject/TolStage/TolStage.h"

#include "../../Object/UI/UICamera/UICamera.h"
#include "../../Object/UI/FrameView/FrameRateView.h"


GameMain::GameMain()
{
}

void GameMain::setup()
{
    // インスタンスを作るところ
    // 3D Objcts
    entities.instantiate<tol::Light>();
    entities.instantiate<tol::Camera>();
    entities.instantiate<tol::EarthSkydome>();
    entities.instantiate<tol::UniverseSkydome>();
    entities.instantiate<tol::Player>();
    entities.instantiate<tol::DebugDraw>();
    entities.instantiate<tol::TolStage>();

    // UI
    ui_entities.instantiate<tol::UICamera>();
    ui_entities.instantiate<tol::FrameRateView>();



    // インスタンスをもらってポインタを渡すところ
    // 3D Objcts
    entities.getInstance<tol::EarthSkydome>()->setTerget(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::UniverseSkydome>()->setTerget(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::Player>()->setCamera(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::TolStage>()->setPlayer(entities.getInstance<tol::Player>());
    entities.getInstance<tol::TolStage>()->setCamera(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::DebugDraw>()->setPlayer(entities.getInstance<tol::Player>());
    entities.getInstance<tol::DebugDraw>()->setCamera(entities.getInstance<tol::Camera>());

    entities.setup();
    ui_entities.setup();
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
void GameMain::shift()
{
    if (env.isPush(ci::app::KeyEvent::KEY_1))
    {
        SoundGet.allStop();
        entities.allDestroy();
        ui_entities.allDestroy();

        SceneCreate<Gacha>(new Gacha());
        SceneManager::instance().get().setup();
    }
}

void GameMain::shutdown()
{
    entities.allDestroy();
    ui_entities.allDestroy();
}
