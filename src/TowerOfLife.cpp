#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "Utility/Easing/Ease.h"
#include "Utility/Time/Time.h"

using namespace ci;
using namespace ci::app;

class TowerOfLife : public AppNative
{
public:
    void prepareSettings(Settings* settings)override;
    void resize()override;
    void shutdown()override;

    void keyDown(KeyEvent event) override;
    void keyUp(KeyEvent event) override;
    void mouseDown(MouseEvent event) override;
    void mouseUp(MouseEvent event) override;

    void setup();
    void update();
    void draw();


    Vec3f testpos = Vec3f(-100.0f, 0, 0);
    CameraOrtho camera_o;
};


void TowerOfLife::prepareSettings(Settings * settings)
{
}

void TowerOfLife::resize()
{
}

void TowerOfLife::shutdown()
{
}

// マウス入力
void TowerOfLife::mouseDown(MouseEvent event)
{
}

void TowerOfLife::mouseUp(MouseEvent event)
{
}

// キー入力
void TowerOfLife::keyDown(KeyEvent event)
{
}

void TowerOfLife::keyUp(KeyEvent event)
{
}


void TowerOfLife::setup()
{
    camera_o = CameraOrtho(-getWindowSize().x / 2,
                           getWindowSize().x / 2,
                           -getWindowSize().y / 2,
                           getWindowSize().y / 2,
                           0, 1);
}

void TowerOfLife::update()
{
}

void TowerOfLife::draw()
{
    gl::clear(Color(0, 0, 0));

    //console() << "Seconds : " << getElapsedSeconds() << std::endl;
   // console() << "Frames : " << getElapsedFrames() << std::endl;

    // イージングサンプル
    {
        gl::pushMatrices();
        gl::setMatrices(camera_o);

        gl::drawSolidCircle(Vec2f(testpos.x, testpos.y), 10);
        if (Easing.isEaseEnd(testpos.x))
        {
            Vec3f startpos = Vec3f(getWindowSize().x / 2 - 50, -getWindowSize().y / 2 + 10, 0);
            Easing.add(testpos, startpos,
                       60, EaseType::CircIn);
            Easing.wait(testpos, 30);
            Easing.add(testpos, Vec3f(startpos.x + 40, startpos.y, 0), 60, EaseType::BounceOut);
            Easing.wait(testpos, 30);
        }
        gl::popMatrices();
    }

    Easing.update();
    tol::Timer.update(getElapsedSeconds());
}

CINDER_APP_NATIVE(TowerOfLife, RendererGl)
