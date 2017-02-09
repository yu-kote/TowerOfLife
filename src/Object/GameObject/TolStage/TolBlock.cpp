#include "TolBlock.h"
#include "../../Component/Components/Material.h"

using namespace ci;
using namespace ci::app;


void tol::TolBlock::setup()
{
    gl::Material m = gl::Material(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                  ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),
                                  80.0f,
                                  ci::ColorA(0.2f, 0.2f, 0.2f));
    addComponent<tol::Material>(tol::Material(m));

    transform.scale = Vec3f(10, 0.5f, 10);
}

void tol::TolBlock::update()
{
    action->update();

}

void tol::TolBlock::draw()
{
    drawBegin();
    pushModelView();
    componentsDraw();

    gl::drawCube(Vec3f::zero(), Vec3f::one());

    popModelView();
    drawEnd();
}

void tol::TolBlock::transDraw()
{

}
