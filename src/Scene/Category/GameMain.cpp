#include "GameMain.h"

#include "../../Task/SoundManager.h"

#include "../../Object/GameObject/Light/Light.h"
#include "../../Object/GameObject/Camera/Camera.h"
#include "../../Object/GameObject/Skydome/Skydomes.h"
#include "../../Object/GameObject/Player/Player.h"
#include "../../Object/GameObject/TolStage/TolStage.h"


GameMain::GameMain()
{
}

void GameMain::setup()
{
    // インスタンスを作るところ
    entities.instantiate<tol::Light>();
    entities.instantiate<tol::Camera>();
    entities.instantiate<tol::EarthSkydome>();
    entities.instantiate<tol::UniverseSkydome>();
    entities.instantiate<tol::Player>();
    entities.instantiate<tol::TolStage>();
    entities.instantiate<tol::TestDraw>();


    // インスタンスをもらってポインタを渡すところ
    entities.getInstance<tol::EarthSkydome>()->setTerget(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::UniverseSkydome>()->setTerget(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::Player>()->setCamera(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::TolStage>()->setPlayer(entities.getInstance<tol::Player>());
    entities.getInstance<tol::TolStage>()->setCamera(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::TestDraw>()->setPlayer(entities.getInstance<tol::Player>());

    entities.setupGameObject();

}

void GameMain::update()
{
    entities.updateGameObject();
    entities.laterUpdateGameObject();
}

void GameMain::draw()
{
    entities.drawGameObject();
    entities.laterDrawGameObject();
}

void GameMain::shift()
{
}

void GameMain::shutdown()
{
    entities.allDestroy();
}
