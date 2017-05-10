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
#include "../../Object/UI/TolUI/GameItem/GameMainUI.h"
#include "../../Object/UI/TolUI/GameMainUI/CountDown/CountDown.h"
#include "../../Object/UI/TolUI/GameMainUI/Pause/Pause.h"


GameMain::GameMain()
{
}

void GameMain::setup()
{
    // インスタンスする
    // 3D Objcts
    entities.instantiate<tol::Light>();
    entities.instantiate<tol::Camera>();
    entities.instantiate<tol::UniverseSkydome>();
    entities.instantiate<tol::EarthSkydome>();
    entities.instantiate<tol::Player>();
    entities.instantiate<tol::PlayerShadow>();
    entities.instantiate<tol::TolStage>();

    // UI
    ui_entities.instantiate<tol::UICamera>();
    ui_entities.instantiate<tol::CountDownCanvas>();
    ui_entities.instantiate<tol::Continue>();
    ui_entities.instantiate<tol::Pause>();
    ui_entities.instantiate<tol::GameMainUI>();

    ui_entities.instantiate<tol::FadeIn>(tol::FadeIn(ci::ColorA(0, 0, 0, 1), 60));
    ui_entities.getInstance<tol::FadeIn>()->fadeStart();
    ui_entities.instantiate<tol::FadeOut>(tol::FadeOut(ci::ColorA(0, 0, 0, 0), 120));

    ui_entities.instantiate<tol::FrameRateView>();

    // インスタンスをもらってポインタを渡すところ
    // 3D Objcts
    entities.getInstance<tol::Camera>()->setTolBlockHolder(entities.getInstance<tol::TolStage>()->getBlockHolder());
    entities.getInstance<tol::Camera>()->setPlayer(entities.getInstance<tol::Player>());
    entities.getInstance<tol::EarthSkydome>()->setTerget(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::UniverseSkydome>()->setTerget(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::Player>()->setCamera(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::TolStage>()->setPlayer(entities.getInstance<tol::Player>());
    entities.getInstance<tol::TolStage>()->setCamera(entities.getInstance<tol::Camera>());
    entities.getInstance<tol::PlayerShadow>()->setPlayer(entities.getInstance<tol::Player>());

    // UI
    ui_entities.getInstance<tol::Continue>()->setPlayer(entities.getInstance<tol::Player>());

    entities.setup();
    ui_entities.setup();

    is_gamestop = false;
    current_gamestop = is_gamestop;
}

void GameMain::countDownStop()
{
    auto count_down = ui_entities.getInstance<tol::CountDownCanvas>();
    if (count_down->isCountDownEnd())
    {
        if (count_down->getIsStart() == false)
        {
            stopObjects(true);
            SoundGet.find("tower_bgm1")->start();
        }
        count_down->start();
    }
    else
    {
        // カウントダウン後に動かすobjectを止めておく
        stopObjects(false);
    }
}

void GameMain::stopObjects(const bool& active)
{
    entities.getInstance<tol::Player>()->setUpdateActive(active);
    entities.getInstance<tol::TolStage>()->setUpdateActive(active);
    ui_entities.getInstance<tol::GameMainUI>()->setUpdateActive(active);
}

void GameMain::gameStop()
{
    if (env.isPadPush(env.BUTTON_10))
    {
        is_gamestop = !is_gamestop;
    }

    if (current_gamestop == is_gamestop)
        return;
    current_gamestop = is_gamestop;

    ui_entities.getInstance<tol::Pause>()->setDrawActive(is_gamestop);

    if (is_gamestop)
    {
        entities.allUpdateActive(false);
        ui_entities.allUpdateActive(false);
    }
    else
    {
        entities.allUpdateActive(true);
        ui_entities.allUpdateActive(true);
    }
}


void GameMain::update()
{
    gameStop();
    countDownStop();

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
    // プレイヤーがまだ動ける状態ならはじきます
    if (!entities.getInstance<tol::Player>()->isNotOperation())
        return;

    auto select_name = ui_entities.getInstance<tol::Continue>()->getSelectButtonName();
    if (select_name == "")
        return;

    // セレクトボタンが二度押されないようにActiveをfalseにします
    ui_entities.getInstance<tol::Continue>()->setUpdateActive(false);
    // フェードアウトさせます
    ui_entities.getInstance<tol::FadeOut>()->fadeStart();

    if (!ui_entities.getInstance<tol::FadeOut>()->isFadeEnd())
        return;

    entities.allDestroy();
    ui_entities.allDestroy();
    Easing.allClear();
    SoundGet.allStop();

    // ゲーム内で手に入れたコインを実体化します
    tol::TolData.coinInstance();
    tol::TolData.save();

    // このシーンに戻ってくるために前のシーンとして保存しておきます
    tol::TolData.prev_scene = SceneCategory::GAMEMAIN;

    if (select_name == "Yes")
        SceneCreate<Gacha>(new Gacha());
    else if (select_name == "No")
        SceneCreate<Title>(new Title());
    
    // 新しいシーンのsetupを呼んでおきます
    SceneManager::instance().get().setup();
}

void GameMain::shutdown()
{
    entities.allDestroy();
    ui_entities.allDestroy();
}
