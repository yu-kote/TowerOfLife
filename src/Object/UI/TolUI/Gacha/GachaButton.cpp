#include "GachaButton.h"
#include "../../../../Utility/Utility.h"
#include "../../../../Utility/Easing/Ease.h"

using namespace ci;
using namespace ci::app;


tol::GachaButton::GachaButton() :
    ButtonBase("Sample")
{
    points.push_back(Vec2f(0.0f, 0.0f));
    points.push_back(Vec2f(100.0f, 0.0f));
    points.push_back(Vec2f(100.0f, 100.0f));
    points.push_back(Vec2f(0.0f, 100.0f));
}

void tol::GachaButton::setup()
{

}

void tol::GachaButton::update()
{
    if (pointToRect(env.mousePosition(), Rectf(points)))
        is_select = true;
    else
        is_select = false;

    if (current_is_select != is_select)
    {
        current_is_select = is_select;
        if (is_select)
            setTexture(TextureGet.find("SamplePush"));
        else
            setTexture(TextureGet.find("Sample"));
    }
}

void tol::GachaButton::draw()
{
    Rectf r = Rectf(points);
    gl::drawSolidRect(r);
}
