#include "TolCoin.h"
#include "../../../Task/ObjDataManager.h"
#include "../../../Utility/Utility.h"
#include "../../Component/Components/Material.h"
#include "../../Component/Components/Texture.h"
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
    addComponent<tol::Texture>(tol::Texture("CoinObj"));

    rotate_speed = 1;
    radius = 1.0f;

    mesh = &ObjDataGet.find("Coin");

    auto size = 0.08f;
    transform.scale = Vec3f(size, size, size);

}

void tol::TolCoin::update()
{
    transform.angle.y += rotate_speed;
    transform.angle.y = std::fmod(transform.angle.y, 360.0f);
}

void tol::TolCoin::draw()
{
    drawBegin();
    pushModelView();
    componentsDraw();

    gl::draw(*mesh);

    popModelView();
    drawEnd();
}

bool tol::TolCoin::isHitToCoin(const ci::Vec3f& pos, float radius_)
{
    return sphereToSphere(transform.position, radius, pos, radius_);
}
