#include "UICamera.h"
#include "../../../Utility/Resize/Resize.h"


using namespace ci;
using namespace ci::app;


tol::UICamera::UICamera()
{
}

void tol::UICamera::setup()
{
    camera.setOrtho(
        0.0f,
        (float)getWindowSize().x,
        (float)getWindowSize().y,
        0.0f,
        0.0f,
        100.0f);
}

void tol::UICamera::update()
{
    WindowResize.setOrthoCameraResize = [&]()
    {
        camera.setOrtho(
            0.0f,
            (float)getWindowSize().x,
            (float)getWindowSize().y,
            0.0f,
            0.0f,
            100.0f);
    };
}

void tol::UICamera::awakeDraw()
{
    gl::enableAlphaBlending();
    gl::pushMatrices();
    gl::setMatrices(camera);
}

void tol::UICamera::laterUpdate()
{
}

void tol::UICamera::laterDraw()
{
    gl::popMatrices();
    gl::disableAlphaBlending();
}
