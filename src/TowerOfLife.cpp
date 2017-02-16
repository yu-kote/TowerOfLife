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

using namespace ci;
using namespace ci::app;

class TowerOfLife : public AppNative
{
public:
    void setup();
    void update();
    void draw();

    void keyDown(KeyEvent event) override;
    void keyUp(KeyEvent event) override;
    void mouseDown(MouseEvent event) override;
    void mouseUp(MouseEvent event) override;

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
    camera_o = CameraOrtho(0,
                           getWindowSize().x,
                           getWindowSize().y,
                           0,
                           0.0f,
                           10.0f);
    pos = Vec3f(getWindowSize().x - 10, getWindowSize().y - 10, 0);

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
    time.update(getElapsedSeconds());
    // イージングの更新
    Easing.update();
}

void TowerOfLife::draw()
{
    gl::clear(Color(0, 0, 0));

    gamemain.draw();


    // お試しイージング
    gl::pushMatrices();
    gl::setMatrices(camera_o);
    gl::color(1, 1, 1);
    gl::drawSolidCircle(Vec2f(pos.x, pos.y), 10);
    if (Easing.isEaseEnd(pos.x))
    {
        Vec3f startpos = Vec3f(getWindowSize().x - 50, getWindowSize().y - 10, 0);
        Easing.add(pos, startpos,
                   60, EaseType::CircIn);
        Easing.wait(pos, 30);
        Easing.add(pos, Vec3f(startpos.x + 40, startpos.y, 0), 60, EaseType::BounceOut);
        Easing.wait(pos, 30);
    }


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

void TowerOfLife::mouseDown(MouseEvent event)
{
    env.mouseDown(event);
}

void TowerOfLife::mouseUp(MouseEvent event)
{
    env.mouseUp(event);
}

CINDER_APP_NATIVE(TowerOfLife, RendererGl)
