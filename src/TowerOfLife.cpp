#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"

#include "Scene/Category/GameMain.h"

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

    CameraOrtho camera_o;
    Vec3f pos;

    // deltatime
    tol::Time time;

    // frame
    Font font;
    Vec2f fpos;
    int prev_frame;

    GameMain gamemain;

    CameraPersp camera;
public:

};

void TowerOfLife::setup()
{
    camera_o = CameraOrtho(0.0f,
        (float)getWindowSize().x,
                           (float)getWindowSize().y,
                           0.0f,
                           0.0f,
                           10.0f);
    pos = Vec3f((float)getWindowSize().x - 10.0f, (float)getWindowSize().y - 10.0f, 0.0f);

    font = Font("Hiragino Maru Gothic ProN W4", 60.0f);
    fpos = Vec2f(1380, 820);
    prev_frame = 0;

    TextureGet.setup();
    SoundGet.setup();
    ObjDataGet.setup();


    gl::enableDepthRead();
    gl::enableDepthWrite();
    gl::enable(GL_CULL_FACE);

    env.padSetup();
    gamemain.setup();

    //Json::StyledWriter writer;

    //std::string s = writer.write(value);
    //console() << s << std::endl;

    //std::ofstream o("block2.json");
    //o << s;
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
    gamemain.shutdown();
    Easing.shutdown();
}

void TowerOfLife::update()
{
    env.padUpdate();
    env.padProcessEvent();
    gamemain.update();
    gamemain.shift();

    // タイマーの更新
    time.update((float)getElapsedSeconds());
    // イージングの更新
    Easing.update();
}

void TowerOfLife::draw()
{
    gl::clear(Color(0, 0, 0));

    gamemain.draw();

    gl::pushMatrices();
    gl::setMatrices(camera_o);

    {// 何フレームか見る
        gl::translate(fpos);

        int frame = static_cast<int>((1000.0f / time.deltaTime()) * 0.001f);
        if (prev_frame > frame + 3 || prev_frame < frame - 3)
        {
            prev_frame = frame;
        }
        gl::drawString(std::to_string(prev_frame),
                       Vec2f::zero(),
                       Color(1.0f, 1.0f, 1.0f),
                       font);
    }
    gl::popMatrices();

    // Paramの更新
    Params->setPosition(Vec2i(0,300));
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
