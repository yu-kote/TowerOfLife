#include "GameMain.h"


#include "../../Object/GameObject/Light/Light.h"
#include "../../Object/GameObject/Camera/Camera.h"
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
    entities.instantiate<tol::Player>();
    entities.instantiate<tol::TolStage>();




    // インスタンスをもらってポインタを渡すところ
    entities.getInstance<tol::Player>()->camera = entities.getInstance<tol::Camera>();
    entities.getInstance<tol::TolStage>()->setPlayer(entities.getInstance<tol::Player>());
    entities.getInstance<tol::TolStage>()->setCamera(entities.getInstance<tol::Camera>());

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
