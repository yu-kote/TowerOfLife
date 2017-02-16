#include "TolCoin.h"
#include "../../../Utility/Utility.h"
#include "../../Component/Components/Material.h"
#include "../../../Utility/Random/Random.h"


using namespace ci;
using namespace ci::app;


void tol::TolCoin::setup()
{
    gl::Material m = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                  80.0f,
                                  ci::ColorA(0.2f, 0.2f, 0.2f));
    addComponent<tol::Material>(tol::Material(m));


    rotate_speed = 1;
    radius = 1.0f;
}

void tol::TolCoin::update()
{
    transform.angle.y += rotate_speed;
    transform.angle.y = std::fmod(transform.angle.y, 360);
}

void tol::TolCoin::draw()
{
    drawBegin();
    pushModelView();
    componentsDraw();

    gl::drawCube(Vec3f::zero(), Vec3f(2, 2, 0.5f));
    gl::drawSphere(Vec3f::zero(), radius);

    popModelView();
    drawEnd();
}

bool tol::TolCoin::isHitToCoin(const ci::Vec3f& pos, float radius_)
{
    return sphereToSphere(transform.position, radius, pos, radius_);
}
