#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"

#include "Tol/TolGameDataManager.h"

#include "Scene/Manager/SceneManager.h"
#include "Scene/Category/GameMain.h"
#include "Scene/Category/Gacha.h"
#include "Scene/Category/Title.h"


#include "Utility/Time/Time.h"
#include "Utility/Easing/Ease.h"
#include "Utility/Utility.h"
#include "Utility/Interface/Interface.h"
#include "Utility/Input/InputEvent.h"
#include "Utility/Resize/Resize.h"

#include "Task/ObjDataManager.h"
#include "Task/SoundManager.h"
#include "Task/TextureManager.h"

#include "jsoncpp/json/json.h"

using namespace ci;
using namespace ci::app;

class TowerOfLife : public AppNative
{
public:
    void setup()    override;
    void update()   override;
    void draw()     override;

    void mouseMove(MouseEvent event) override;
    void mouseDrag(MouseEvent event) override;
    void mouseDown(MouseEvent event) override;
    void mouseUp(MouseEvent event)   override;
    void keyDown(KeyEvent event)     override;
    void keyUp(KeyEvent event)       override;

    void resize()override;
    void prepareSettings(Settings *settings)override;
    void shutdown()override;

public:

};

void TowerOfLife::setup()
{
    TextureGet.setup();
    SoundGet.setup();
    ObjDataGet.setup();

    gl::enable(GL_CULL_FACE);

    env.padSetup();

    SceneCreate<Title>(new Title());
    SceneManager::instance().get().setup();

    //Json::StyledWriter writer;

    //std::string s = writer.write(value);
    //console() << s << std::endl;

    //std::ofstream o("block2.json");
    //o << s;

    Params->setPosition(Vec2i(0, 300));
}


void TowerOfLife::resize()
{
    WindowResize.resize();
}

void TowerOfLife::prepareSettings(Settings * settings)
{
    settings->setWindowSize(Vec2f(WindowSize::WIDTH, WindowSize::HEIGHT));
}

void TowerOfLife::shutdown()
{
    env.padShutDown();
    SceneManager::instance().get().shutdown();
    Easing.allClear();
}

void TowerOfLife::update()
{
    env.padUpdate();
    env.padProcessEvent();

    SceneManager::instance().get().update();
    SceneManager::instance().get().shift();

    // タイマーの更新
    tol::Timer.update((float)getElapsedSeconds());
    // イージングの更新
    Easing.update();
}

void TowerOfLife::draw()
{
    gl::clear(Color(0, 0, 0));

    SceneManager::instance().get().draw();

    // Paramの更新
    Params->draw();
}

void TowerOfLife::keyDown(KeyEvent event)
{
    env.keyDown(event);
}

void TowerOfLife::keyUp(KeyEvent event)
{
    env.keyUp(event);
}

void TowerOfLife::mouseMove(MouseEvent event)
{
    env.mouseMove(event);
}

void TowerOfLife::mouseDrag(MouseEvent event)
{
    env.mouseDrag(event);
}

void TowerOfLife::mouseDown(MouseEvent event)
{
    env.mouseDown(event);
}

void TowerOfLife::mouseUp(MouseEvent event)
{
    env.mouseUp(event);
}

CINDER_APP_NATIVE(TowerOfLife, RendererGl)
