#include "GachaButton.h"
#include "../../../../Utility/Utility.h"
#include "../../../../Utility/Easing/Ease.h"

using namespace ci;
using namespace ci::app;


tol::GachaButton::GachaButton()
//  : ButtonBase("Sample")
{
}

void tol::GachaButton::setup()
{
    transform.position = Vec3f(500, 500, 0.0f);
    points.push_back(Vec2f(0.0f, 0.0f));
    points.push_back(Vec2f(100.0f, 0.0f));
    points.push_back(Vec2f(150.0f, 50.0f));
    points.push_back(Vec2f(50.0f, 100.0f));
    points.push_back(Vec2f(0.0f, 100.0f));

    addComponent<tol::Color>(tol::Color(1.0f, 1.0f, 1.0f));
    color = getComponent<tol::Color>();
}

void tol::GachaButton::update()
{
    if (pointToQuadrangle(mouse_position, points))
        is_select = true;
    else
        is_select = false;

    if (current_is_select != is_select)
    {
        current_is_select = is_select;
        if (is_select)
        {
            color->setColor(1.0f, 0.0f, 0.0f);
            //setTexture(TextureGet.find("SamplePush"));
        }
        else
        {
            color->setColor(ColorA::white());
            //setTexture(TextureGet.find("Sample"));
        }
    }
}

void tol::GachaButton::draw()
{
    Rectf r = Rectf(points);
    //gl::drawSolidRect(r);

    for (int i = 0; i < points.size(); i++)
    {
        Vec3f s = Vec3f(points[i].x, points[i].y, 0.0f);
        Vec3f e;
        if (i < points.size() - 1)
            e = Vec3f(points[i + 1].x, points[i + 1].y, 0.0f);
        else
            e = Vec3f(points[0].x, points[0].y, 0.0f);

        gl::drawVector(s, e);
    }
}
