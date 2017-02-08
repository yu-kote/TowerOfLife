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
    entities.instantiate<tol::Light>();
    entities.instantiate<tol::Camera>();
    entities.instantiate<tol::Player>();
    entities.instantiate<tol::TolStage>();

    entities.getInstance<tol::Player>()->camera = entities.getInstance<tol::Camera>();
    entities.setupGameObject();
}

void GameMain::update()
{
    entities.updateGameObject();
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
